(function(undefined) {
  'use strict';

  /**
   * magik Namespace
   * ==================
   *
   * Register some global configuration.
   */
  var _config = {
    domino: {
      verbose: true
    },
    realtime: {
      debug: false
    }
  };

  /**
   * Exporting
   * ----------
   */
  utilities.pkg('magik.config', _config);
}).call(this);
