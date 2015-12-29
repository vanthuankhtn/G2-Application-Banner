var Banner = {
    request: function () {
        if(!Banner.is_mobile()) {
            return;
        }

        var close_flag = jQuery.cookie("close_g2banner_flag");
        if(close_flag) {
            return;
        }

        jQuery.get("/g2app-banner", function (data) {
            if(!data) {
                return;
            }
            Banner.render(data);
        });
    },

    render: function (data) {
        var container = '<div class="app-banner" id="app-banner">';
        container += '<div class="smart-app-banner ' + data.type + '">';
        container += '<div class="app-wrapper"><a class="close">x</a>';
        container += '<img src="' + data.image_url + '"/>';

        container += '<div class="app-content">';
        container += '<h2>' + data.name + '</h2><p>' + data.description + '</p>';
        container += Banner.rating(data.rating);
        container += '</div>';

        container += '<a href="' + data.app_url + '" class="view" target="_blank">' + Drupal.t('View') + '</a>';
        container += '</div>';
        container += '</div>';
        container += '</div>';

        jQuery('body').prepend(jQuery(container).fadeIn('slow'));
        Banner.close();
    },

    rating: function (rate) {
        var remainder = rate.substr(rate.indexOf('.') + 1, 4);
        remainder = '0.' + Number(remainder);

        var rating = '<div class="rate">';
        for (var index = 1; index <= 5; index++) {
            if (index <= rate) {
                rating += '<span class="full"></span>';
                continue;
            }

            if(0.3 <= remainder && remainder <=  0.7) {
                rating += '<span class="half"></span>';
                continue;
            } else if(remainder > 0.7) {
                rating += '<span class="full"></span>';
                continue;
            }

            rating += '<span></span>';
        }

        rating += '</div>';
        return rating;
    },

    close: function () {
        jQuery('.close').click(function(){
            jQuery(this).parent().parent().fadeOut("slow", function() {
                jQuery.cookie("close_g2banner_flag", true, 300);
            });
        });
    },

    is_mobile: function() {
        var ua = navigator.userAgent;
        var checker = {
            ios: ua.match(/(iPhone|iPod|iPad)/),
            android: ua.match(/Android/)
        };

        return (checker.android || checker.ios);
    }
};

jQuery(function () {
    Banner.request();
});