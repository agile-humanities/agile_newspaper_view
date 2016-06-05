
(function ($) {
    Drupal.behaviors.agile_newspaper = {
        'attach': function (context) {
            $('.loader_gif').hide();
            var switcher = function () {
                var selected = $('#agile_year_select option:selected').text();
                $.ajax({
                    url: Drupal.settings.agile_newspaper_view.callback_path,
                    type: "POST",
                    beforeSend: function () {
                        $('.loader_gif').show();
                    },
                    data: {
                        pid: Drupal.settings.agile_newspaper_view.pid,
                        year: selected
                    },
                    success: function (results, status, xhr) {
                        $('#current_year').html(results);
                        $(".month .fieldset-legend").each(function () {
                            var span_text = '<a class="fieldset-title">'
                            span_text += '<span class="fieldset-legend-prefix element-invisible">Hide</span>';
                            span_text += $(this).text();
                            span_text += '</a><span class="summary" />';
                            $(this).html(span_text);
                        })
                        $('#current_year').find('a.fieldset-title').click(function () {
                            Drupal.toggleFieldset($(this).closest('fieldset.collapsible'));
                        });
                        $('.loader_gif').hide();
                    },
                    error: function (data, status, xhd) {
                        console.log("The function switcher has failed");
                    }
                });
            }
            $('#agile_year_select').change(switcher)
            switcher();
        }
    };
})(jQuery);