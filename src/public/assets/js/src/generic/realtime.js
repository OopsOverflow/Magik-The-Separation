(function(undefined) {
  'use strict';

  /**
   * Realtime Utilities
   * ===================
   *
   * Realtime abstraction to plug socket.io into domino.
   */
  let socketC= new WebSocket("ws://localhost:3030");
  // Connecting
  var socket = io.connect();

  // Helpers
  function addSide(o, side) {
    return _.merge((o || {}), {side: side});
  }

  function gameCheck(field){
    return (field !== undefined) ? field : null;
  }

  // Functions namespace
  var _realtime = {
    connect: function(url, cb) {
      socket.get(url, cb);
    },
    bootstrap: function(o) {
      o.dispatchRealtimeEvent = function(head, body) {
        this.dispatchEvent('realtime.send', {
          head: head,
          body: addSide(body, 'op')
        })
        let obj = {head, "__MESSAGE__": "message", ...addSide(body, 'op') }
        socketC.send(JSON.stringify(obj));
      };

      o.dispatchBothEvents = function(head, body) {
        this.dispatchRealtimeEvent(head, body);
        this.dispatchEvent(head, addSide(body, 'my'));
        let obj = {head, "__MESSAGE__": "message", ...addSide(body, 'my') }
        socketC.send(JSON.stringify(obj));
      };
    },
    domino: function(game_id) {
      return {
        module: function() {
          var _this = this;

          socket.on('game', function(e) {
            if (e.verb === 'updated') {
              _this.dispatchEvent('realtime.receive', e.data);

              // parse body
                const game = e.data.body.game;
                if (game !== undefined) {
                  var b = {
                    id: game.id,
                    createdAt: game.createdAt,
                    player1: game.player1.user.name,
                    player2: game.player2.user.name,
                    connection: game.player1.connected && game.player2.connected
                  }
                  let obj = {"__MESSAGE__": "message", "head": e.data.head, ...b}
                  socketC.send(JSON.stringify(obj));
                  console.log("KKKK");
                  console.log(e.data.body.game);
                }
            }
          }
          );
        },
        hacks: [
          {
            triggers: 'realtime.receive',
            method: function(e) {
              this.dispatchEvent(e.data.head, e.data.body);
            }
          },
          {
            triggers: 'realtime.send',
            method: function(e) {
              var d = {
                id: this.get('gameId'),
                debug: this.get('debug'),
                head: e.data.head,
                body: (e.data.body !== undefined) ? e.data.body : null
              };
              // Sending through socket
              socket.post('/playground/' + game_id + '/message', d);

              d = {
                id: this.get('gameId'),
                head: e.data.head
              };
              let body = (e.data.body !== undefined) ? e.data.body : null;

              let obj = {"url": ("playground/"+game_id+"/message"), "__MESSAGE__": "message",...d, ...body};
              socketC.send(JSON.stringify(obj));
            }
          }
        ]
      };
    }
  };

  // Firehose Debug
  if (magik.config.realtime.debug)
    socket.get('/firehose', function() {

      console.log('Firehose online...');

      // Attach a listener which fires every time Sails publishes
      // message to the firehose.
      socket.on('firehose', function(m) {
        console.log('FIREHOSE (debug): Sails published a message ::\n', m);
      });
    });

  /**
   * Exporting
   * ----------
   */
  this.realtime = _realtime;
  this.socket = socket;
}).call(this);
