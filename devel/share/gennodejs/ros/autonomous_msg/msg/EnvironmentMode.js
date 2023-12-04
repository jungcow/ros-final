// Auto-generated. Do not edit!

// (in-package autonomous_msg.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class EnvironmentMode {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ice_mode = null;
      this.hill_mode = null;
    }
    else {
      if (initObj.hasOwnProperty('ice_mode')) {
        this.ice_mode = initObj.ice_mode
      }
      else {
        this.ice_mode = '';
      }
      if (initObj.hasOwnProperty('hill_mode')) {
        this.hill_mode = initObj.hill_mode
      }
      else {
        this.hill_mode = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type EnvironmentMode
    // Serialize message field [ice_mode]
    bufferOffset = _serializer.string(obj.ice_mode, buffer, bufferOffset);
    // Serialize message field [hill_mode]
    bufferOffset = _serializer.string(obj.hill_mode, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type EnvironmentMode
    let len;
    let data = new EnvironmentMode(null);
    // Deserialize message field [ice_mode]
    data.ice_mode = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [hill_mode]
    data.hill_mode = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.ice_mode);
    length += _getByteLength(object.hill_mode);
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autonomous_msg/EnvironmentMode';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'df53af7b00c9079615c2b52e2721e823';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string ice_mode
    string hill_mode
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new EnvironmentMode(null);
    if (msg.ice_mode !== undefined) {
      resolved.ice_mode = msg.ice_mode;
    }
    else {
      resolved.ice_mode = ''
    }

    if (msg.hill_mode !== undefined) {
      resolved.hill_mode = msg.hill_mode;
    }
    else {
      resolved.hill_mode = ''
    }

    return resolved;
    }
};

module.exports = EnvironmentMode;
