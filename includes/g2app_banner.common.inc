<?php

/**
 * Get apple app information
 * @param $app_id
 * @return mixed|null
 */
function g2app_banner_itune_information_get($app_id, $language) {
  $result = &drupal_static(__FUNCTION__);
  if(isset($result)) {
    return $result;
  }

  $result = cache_get(G2CACHE_ITUNE_APP_INFO);
  if(!empty($result)) {
    return $result->data;
  }

  $app_url = G2ITUNE_APP_URL;
  $app_url .= '?id=' . $app_id . '&country=fr';

  $response = file_get_contents($app_url);
  if(empty($response)) {
    return null;
  }

  $expired_time = REQUEST_TIME + variable_get('expired_time', G2CACHE_EXPIRED_TIME);
  $response = json_decode($response);
  $app_info = $response->results;
  $app_info = reset($app_info);

  $result = array(
    'type' => G2IS_IOS,
    'name' => $app_info->artistName,
    'image_url' => $app_info->artworkUrl60,
    'app_url' => $app_info->trackViewUrl,
    'description' => g2app_banner_word_trim($app_info->description),
    'rating' => str_replace(',', '.',   $app_info->averageUserRating),
  );

  cache_set(G2CACHE_ITUNE_APP_INFO, $result, 'cache', $expired_time);
  return $result;
}

/**
 * Get google app information
 * @param $app_id
 */
function g2app_banner_google_information_get($app_id, $language) {
  $result = &drupal_static(__FUNCTION__);
  if(isset($result)) {
    return $result;
  }

  $result = cache_get(G2CACHE_GOOGLE_APP_INFO);
  if(!empty($result)) {
    return $result->data;
  }

  $module_path = drupal_get_path('module', 'g2app_banner');
  include_once($module_path . '/plugins/playStoreApi.php');

  $class_init = new PlayStoreApi;
  $item_info = $class_init->itemInfo($app_id, $language);
  if($item_info == 0) {
    return null;
  }

  $expired_time = REQUEST_TIME + variable_get('expired_time', G2CACHE_EXPIRED_TIME);
  $item_info = $item_info['General'][0];

  $result = array(
    'type' => G2IS_ANDROID,
    'name' => $item_info->app_title,
    'image_url' => $item_info->banner_image,
    'description' => g2app_banner_word_trim($item_info->html_app_description),
    'rating' => str_replace(',', '.', $item_info->score),
    'app_url' => $item_info->app_store_url,
  );

  cache_set(G2CACHE_GOOGLE_APP_INFO, $result, 'cache', $expired_time);
  return $result;
}

/**
 * Trim word
 * @param $sentence
 * @return string
 */
function g2app_banner_word_trim($sentence) {
  $result = $sentence;
  if(str_word_count($sentence) > G2MAX_WORD) {
    $result = implode(' ', array_slice(explode(' ', $sentence), 0 , G2MAX_WORD)) . '...' ;
  }

  return $result;
}

/**
 * Get app information
 */
function g2app_banner_information_get() {
  global $language;
  $device = app_banner_device_get();
  $app_info = null;

  if(!$device) {
    return $app_info;
  }

  if($device == G2IS_IOS) {
    $app_info = g2app_banner_itune_information_get(variable_get('apple_app_id', G2APPLE_ID_DEFAULT), $language->language);
  } else {
    $app_info = g2app_banner_google_information_get(variable_get('android_app_id', G2GOOGLE_ID_DEFAULT), $language->language);
  }

  drupal_json_output($app_info);
}