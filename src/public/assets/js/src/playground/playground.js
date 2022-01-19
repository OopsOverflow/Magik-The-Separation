(function(undefined) {
  'use strict';

  /**
   * Playground Namespace
   * =====================
   *
   * Register some global configuration.
   */
  var _config = {
    baseZ: 30,
    maxZ: 30
  };

  var _drivers = {
    my: new magik.driver('my'),
    op: new magik.driver('op')
  };

  /**
   * Exporting
   * ----------
   */
  utilities.pkg('playground.config', _config);
  utilities.pkg('playground.drivers', _drivers);
}).call(this);
