;(function(undefined) {
  'use strict';

  // Checking whether the current driver is set
  if (this.currentDriver === undefined)
    throw 'magik.template: error, current driver is not defined.';
  else
    var _driver = this.currentDriver;

  // Templates
  //-----------
  function CardTemplate(id_prefix) {
    var _this = this;

    // Properties
    this.prefix = id_prefix || 'card';
    this.index = -1;

    // Getting necessary templates
    function compile(id) {
      var $tpl = $(id);

      if ($tpl.length)
        return Handlebars.compile($tpl.html());
    }
    this.templates = {
      standard: compile('#tpl_card'),
      dummy: compile('#tpl_dummy_card'),
      search: compile('#tpl_search_card')
    };

    // Special cases
    function specialCases(card, context) {

      if (card.types !== undefined && ~card.types.indexOf('Land'))
        context.type = 'land';
      else if (card.types !== undefined && ~card.types.indexOf('Enchantment'))
        context.type = 'enchantment';

      return context;
    }

    // Rendering methods
    this.render = function(card, indexOverride) {
      var index = (indexOverride) ? indexOverride : ++this.index,
          context = {
            id_prefix: this.prefix,
            number: index,
            multiverseid: card.multiverseid,
            src: _driver(card),
            side: this.prefix,
            name: card.name,
            set: card.set
          };

      // Apply special cases
      context = specialCases(card, context);

      // Render
      return this.templates.standard(context);
    };

    this.renderDummy = function() {
      return this.templates.dummy({side: this.prefix});
    };

    this.renderSearch = function(card, index_override) {
      return this.templates.search({
        number: index_override,
        src: _driver(card)
      });
    };
  }

  // Exporting
  //-----------
  utilities.pkg('magik.driver', CardTemplate);
}).call(this);
