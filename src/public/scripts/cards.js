// Creating a slightly different json file for cards.

// Loading sets
var _ = require('lodash'),
    fs = require('fs'),
    sets = require('../database/mtg.json'),
    numbers = require('../database/numbers.json');

// Main Loop
var cards_array = [],
    missing_set_numbers = [];

var blacklist = [
  'DKM',
  'HHO',
  'DPA'
];

for (var set in sets) {

  // Looping through cards
  sets[set].cards.forEach(function(card, index) {
    card['set'] = set;

    if (~blacklist.indexOf(card.set))
      return;

    // Registering missing set
    if(!~missing_set_numbers.indexOf(set) && card.number === undefined) {
      missing_set_numbers.push(set);
    }

    // Indicating card number if missing
    // TODO: refine for several identical cards such as lands
    if (card.number === undefined && numbers[set] !== undefined) {
      if(!~numbers[set].indexOf(card.name))
        console.log(card.name, card.set);

      card.number = numbers[set].indexOf(card.name);
    }

    cards_array.push(card);
  });
}

// Debug
console.log(missing_set_numbers);

// Writing in file
cards_array.reverse();
fs.writeFileSync('./database/cards.json', JSON.stringify(cards_array));
