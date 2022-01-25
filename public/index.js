
function SocketWrapper(init)
{
    this.socket = new SimpleWebsocket(init);
    this.messageHandlers = {};

    var that = this;
    this.socket.on('data', function(data)
    {
        //Extract the message type
        var messageData = JSON.parse(data);
        var messageType = messageData['__MESSAGE__'];
        delete messageData['__MESSAGE__'];

        //If any handlers have been registered for the message type, invoke them
        if (that.messageHandlers[messageType] !== undefined)
        {
            for (index in that.messageHandlers[messageType]) {
                that.messageHandlers[messageType][index](messageData);
            }
        }
    });
}

SocketWrapper.prototype.on = function(event, handler)
{
    //If a standard event was specified, forward the registration to the socket's event emitter
    if (['connect', 'close', 'data', 'error'].indexOf(event) !== -1) {
        this.socket.on(event, handler);
    }
    else
    {
        //The event names a message type
        if (this.messageHandlers[event] === undefined) {
            this.messageHandlers[event] = [];
        }
        this.messageHandlers[event].push(handler);
    }
}

SocketWrapper.prototype.send = function(message, payload)
{
    //Copy the values from the payload object, if one was supplied
    var payloadCopy = {};
    if (payload !== undefined && payload !== null)
    {
        var keys = Object.keys(payload);
        for (index in keys)
        {
            var key = keys[index];
            payloadCopy[key] = payload[key];
        }
    }

    payloadCopy['__MESSAGE__'] = message;
    this.socket.send(JSON.stringify(payloadCopy));
}

function log(text)
{
    var outputElem = $('#output');
    outputElem.text( outputElem.text() + text + '\n' );
}

$(document).ready(function()
{
    var socket = new SocketWrapper("ws://127.0.0.1:3030");

    //Generic events

    socket.on('connect', function() {
        log("socket is connected!");
    });

    socket.on('data', function(data) {
        log('got message: ' + data)
    });

    socket.on('close', function() {
        log("socket is disconnected!");
    });

    socket.on('error', function(err) {
        log("Error: " + err);
    });

    //Specific message type handlers

    socket.on('userInput', function(args) {
        log("Received user input: \"" + args['input'] + "\"");
    });

    $('#send').click(function() {
        socket.send($('#message').val(), JSON.parse($('#args').val()));
    });
});