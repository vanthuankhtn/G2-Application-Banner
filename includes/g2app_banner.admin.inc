<?php
function g2app_banner_setting_form() {
  $form['desc'] = array(
    '#markup' => '<div>' . t('G2 Application Banner make you feel happy with website.') . '</div>',
  );

  $form['app_ids_group'] = array(
    '#type' => 'fieldset',
    '#title' => t('Smart App Banner Settings - Application ID'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['app_ids_group']['g2apple_app_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Apple Application ID'),
    '#description' => t('Apple application id'),
    '#required' => TRUE,
    '#default_value' => variable_get('g2apple_app_id', G2APPLE_ID_DEFAULT),
  );

  $form['app_ids_group']['g2android_app_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Google Appication ID'),
    '#description' => t('Google application id'),
    '#required' => TRUE,
    '#default_value' => variable_get('g2android_app_id', G2GOOGLE_ID_DEFAULT),
  );

  $form['app_data_config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Smart App Banner Settings - Data configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['app_data_config']['g2expired_time'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Cache Expired Time'),
    '#description' => t('Refesh new data from Apple/Google.'),
    '#default_value' => variable_get('g2expired_time', G2CACHE_EXPIRED_TIME),
  );

  return system_settings_form($form);
}