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

class EnvironmentModeArea {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ice_x = null;
      this.ice_y = null;
      this.ice_radius = null;
      this.hill_x = null;
      this.hill_y = null;
      this.hill_slope_angle = null;
    }
    else {
      if (initObj.hasOwnProperty('ice_x')) {
        this.ice_x = initObj.ice_x
      }
      else {
        this.ice_x = [];
      }
      if (initObj.hasOwnProperty('ice_y')) {
        this.ice_y = initObj.ice_y
      }
      else {
        this.ice_y = [];
      }
      if (initObj.hasOwnProperty('ice_radius')) {
        this.ice_radius = initObj.ice_radius
      }
      else {
        this.ice_radius = [];
      }
      if (initObj.hasOwnProperty('hill_x')) {
        this.hill_x = initObj.hill_x
      }
      else {
        this.hill_x = [];
      }
      if (initObj.hasOwnProperty('hill_y')) {
        this.hill_y = initObj.hill_y
      }
      else {
        this.hill_y = [];
      }
      if (initObj.hasOwnProperty('hill_slope_angle')) {
        this.hill_slope_angle = initObj.hill_slope_angle
      }
      else {
        this.hill_slope_angle = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type EnvironmentModeArea
    // Serialize message field [ice_x]
    bufferOffset = _arraySerializer.float64(obj.ice_x, buffer, bufferOffset, null);
    // Serialize message field [ice_y]
    bufferOffset = _arraySerializer.float64(obj.ice_y, buffer, bufferOffset, null);
    // Serialize message field [ice_radius]
    bufferOffset = _arraySerializer.float64(obj.ice_radius, buffer, bufferOffset, null);
    // Serialize message field [hill_x]
    bufferOffset = _arraySerializer.float64(obj.hill_x, buffer, bufferOffset, null);
    // Serialize message field [hill_y]
    bufferOffset = _arraySerializer.float64(obj.hill_y, buffer, bufferOffset, null);
    // Serialize message field [hill_slope_angle]
    bufferOffset = _arraySerializer.float64(obj.hill_slope_angle, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type EnvironmentModeArea
    let len;
    let data = new EnvironmentModeArea(null);
    // Deserialize message field [ice_x]
    data.ice_x = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [ice_y]
    data.ice_y = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [ice_radius]
    data.ice_radius = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [hill_x]
    data.hill_x = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [hill_y]
    data.hill_y = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [hill_slope_angle]
    data.hill_slope_angle = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.ice_x.length;
    length += 8 * object.ice_y.length;
    length += 8 * object.ice_radius.length;
    length += 8 * object.hill_x.length;
    length += 8 * object.hill_y.length;
    length += 8 * object.hill_slope_angle.length;
    return length + 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autonomous_msg/EnvironmentModeArea';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'aa04ea7b504bc5eedff12056d464548d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[] ice_x
    float64[] ice_y
    float64[] ice_radius
    float64[] hill_x
    float64[] hill_y
    float64[] hill_slope_angle
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new EnvironmentModeArea(null);
    if (msg.ice_x !== undefined) {
      resolved.ice_x = msg.ice_x;
    }
    else {
      resolved.ice_x = []
    }

    if (msg.ice_y !== undefined) {
      resolved.ice_y = msg.ice_y;
    }
    else {
      resolved.ice_y = []
    }

    if (msg.ice_radius !== undefined) {
      resolved.ice_radius = msg.ice_radius;
    }
    else {
      resolved.ice_radius = []
    }

    if (msg.hill_x !== undefined) {
      resolved.hill_x = msg.hill_x;
    }
    else {
      resolved.hill_x = []
    }

    if (msg.hill_y !== undefined) {
      resolved.hill_y = msg.hill_y;
    }
    else {
      resolved.hill_y = []
    }

    if (msg.hill_slope_angle !== undefined) {
      resolved.hill_slope_angle = msg.hill_slope_angle;
    }
    else {
      resolved.hill_slope_angle = []
    }

    return resolved;
    }
};

module.exports = EnvironmentModeArea;
