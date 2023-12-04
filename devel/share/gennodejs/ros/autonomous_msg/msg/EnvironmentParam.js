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

class EnvironmentParam {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.fyf_max = null;
      this.fyr_max = null;
      this.slope_angle = null;
    }
    else {
      if (initObj.hasOwnProperty('fyf_max')) {
        this.fyf_max = initObj.fyf_max
      }
      else {
        this.fyf_max = 0.0;
      }
      if (initObj.hasOwnProperty('fyr_max')) {
        this.fyr_max = initObj.fyr_max
      }
      else {
        this.fyr_max = 0.0;
      }
      if (initObj.hasOwnProperty('slope_angle')) {
        this.slope_angle = initObj.slope_angle
      }
      else {
        this.slope_angle = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type EnvironmentParam
    // Serialize message field [fyf_max]
    bufferOffset = _serializer.float64(obj.fyf_max, buffer, bufferOffset);
    // Serialize message field [fyr_max]
    bufferOffset = _serializer.float64(obj.fyr_max, buffer, bufferOffset);
    // Serialize message field [slope_angle]
    bufferOffset = _serializer.float64(obj.slope_angle, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type EnvironmentParam
    let len;
    let data = new EnvironmentParam(null);
    // Deserialize message field [fyf_max]
    data.fyf_max = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [fyr_max]
    data.fyr_max = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [slope_angle]
    data.slope_angle = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autonomous_msg/EnvironmentParam';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f757b3e255dfef4f680d3558f78ceb06';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 fyf_max
    float64 fyr_max
    float64 slope_angle
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new EnvironmentParam(null);
    if (msg.fyf_max !== undefined) {
      resolved.fyf_max = msg.fyf_max;
    }
    else {
      resolved.fyf_max = 0.0
    }

    if (msg.fyr_max !== undefined) {
      resolved.fyr_max = msg.fyr_max;
    }
    else {
      resolved.fyr_max = 0.0
    }

    if (msg.slope_angle !== undefined) {
      resolved.slope_angle = msg.slope_angle;
    }
    else {
      resolved.slope_angle = 0.0
    }

    return resolved;
    }
};

module.exports = EnvironmentParam;
