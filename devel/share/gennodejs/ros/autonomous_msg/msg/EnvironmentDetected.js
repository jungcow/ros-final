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

class EnvironmentDetected {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ice_param = null;
      this.ice_mode = null;
    }
    else {
      if (initObj.hasOwnProperty('ice_param')) {
        this.ice_param = initObj.ice_param
      }
      else {
        this.ice_param = 0.0;
      }
      if (initObj.hasOwnProperty('ice_mode')) {
        this.ice_mode = initObj.ice_mode
      }
      else {
        this.ice_mode = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type EnvironmentDetected
    // Serialize message field [ice_param]
    bufferOffset = _serializer.float64(obj.ice_param, buffer, bufferOffset);
    // Serialize message field [ice_mode]
    bufferOffset = _serializer.string(obj.ice_mode, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type EnvironmentDetected
    let len;
    let data = new EnvironmentDetected(null);
    // Deserialize message field [ice_param]
    data.ice_param = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [ice_mode]
    data.ice_mode = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.ice_mode);
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autonomous_msg/EnvironmentDetected';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '57850e5a040808185fbe00e153e12c75';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 ice_param
    string ice_mode
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new EnvironmentDetected(null);
    if (msg.ice_param !== undefined) {
      resolved.ice_param = msg.ice_param;
    }
    else {
      resolved.ice_param = 0.0
    }

    if (msg.ice_mode !== undefined) {
      resolved.ice_mode = msg.ice_mode;
    }
    else {
      resolved.ice_mode = ''
    }

    return resolved;
    }
};

module.exports = EnvironmentDetected;
