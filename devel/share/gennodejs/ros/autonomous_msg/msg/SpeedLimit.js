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

class SpeedLimit {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.curr_limit = null;
      this.next_limit = null;
      this.dist_left = null;
    }
    else {
      if (initObj.hasOwnProperty('curr_limit')) {
        this.curr_limit = initObj.curr_limit
      }
      else {
        this.curr_limit = 0.0;
      }
      if (initObj.hasOwnProperty('next_limit')) {
        this.next_limit = initObj.next_limit
      }
      else {
        this.next_limit = 0.0;
      }
      if (initObj.hasOwnProperty('dist_left')) {
        this.dist_left = initObj.dist_left
      }
      else {
        this.dist_left = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SpeedLimit
    // Serialize message field [curr_limit]
    bufferOffset = _serializer.float64(obj.curr_limit, buffer, bufferOffset);
    // Serialize message field [next_limit]
    bufferOffset = _serializer.float64(obj.next_limit, buffer, bufferOffset);
    // Serialize message field [dist_left]
    bufferOffset = _serializer.float64(obj.dist_left, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SpeedLimit
    let len;
    let data = new SpeedLimit(null);
    // Deserialize message field [curr_limit]
    data.curr_limit = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [next_limit]
    data.next_limit = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [dist_left]
    data.dist_left = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autonomous_msg/SpeedLimit';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6811f8ec87f49f482a9d61cafc2ca244';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 curr_limit
    float64 next_limit
    float64 dist_left
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SpeedLimit(null);
    if (msg.curr_limit !== undefined) {
      resolved.curr_limit = msg.curr_limit;
    }
    else {
      resolved.curr_limit = 0.0
    }

    if (msg.next_limit !== undefined) {
      resolved.next_limit = msg.next_limit;
    }
    else {
      resolved.next_limit = 0.0
    }

    if (msg.dist_left !== undefined) {
      resolved.dist_left = msg.dist_left;
    }
    else {
      resolved.dist_left = 0.0
    }

    return resolved;
    }
};

module.exports = SpeedLimit;
