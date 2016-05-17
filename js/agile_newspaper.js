
(function ($) {
    Drupal.behaviors.agile_newspaper = {
        'attach': function (context) {
            $('.vertical-tab-button').hide();
            $('.vertical-tabs-panes').first().hide(); // Hide the 1904 tab
            $('#agile_year_select').change(function(){
                var selected = $('#agile_year_select option:selected').text();
                var selector = '.fieldset-legend:contains(' + selected + ')';
                var active = $(selector).closest('fieldset');
                console.log(active)
                $('#current_year').html(active.html());
                
            })
            
        }
    };
})(jQuery);