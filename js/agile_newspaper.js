
(function ($) {
    Drupal.behaviors.agile_newspaper = {
        'attach': function (context) {
            $(".month").addClass('collapsed');
            var switcher = function () {
                var selected = $('#agile_year_select option:selected').text();
                var selector = '.fieldset-legend:contains(' + selected + ')';
                var active = $(selector).closest('.form-wrapper').wrap('<fieldset class="form-wrapper"></fieldset>');
                $('#current_year').html(active.html());
                $('#current_year').find('a.fieldset-title').click(function () {
                    Drupal.toggleFieldset($(this).closest('fieldset.collapsible'));
                });
            }
            $('.vertical-tab-button').hide();
            $('.vertical-tabs-panes').first().hide();
            switcher();
            $('#agile_year_select').change(switcher)
        }
    };
})(jQuery);