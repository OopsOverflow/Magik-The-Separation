;(function(undefined) {

  // Properties
  //------------
  var urls = {
    multiverseid: 'http://mtgimage.com/multiverseid/',
    cardname: 'http://mtgimage.com/set/'
  };

  // Driver
  //--------
  this.currentDriver = function(card) {

    if (card.multiverseid)
      return urls.multiverseid + card.multiverseid + '.jpg';
    else
      return urls.cardname + card.set + '/' + card.name + '.jpg';
  };
}).call(this);
