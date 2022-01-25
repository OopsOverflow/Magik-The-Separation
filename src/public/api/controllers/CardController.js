/**
 * CardController.js 
 *
 * @description ::
 * @docs        :: http://sailsjs.org/#!documentation/controllers
 */
var card_library = require('../libraries/Card');

module.exports = {
  single_card: function(req, res) {
    var card = card_library.get(req.param('id'));

    if (card)
      res.json(card);
    else
      res.notFound();
  },
  batch_cards: function(req, res) {
    var batch = JSON.parse(req.param('cards'));

    res.json(card_library.getByIdArray(batch));
  },
  search: function(req, res) {
    res.json(card_library.searchByName(req.param('query')));
  }
};
