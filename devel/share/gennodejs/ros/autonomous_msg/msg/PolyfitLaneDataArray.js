// Auto-generated. Do not edit!

// (in-package autonomous_msg.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let PolyfitLaneData = require('./PolyfitLaneData.js');

//-----------------------------------------------------------

class PolyfitLaneDataArray {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.frame_id = null;
      this.polyfitLanes = null;
    }
    else {
      if (initObj.hasOwnProperty('frame_id')) {
        this.frame_id = initObj.frame_id
      }
      else {
        this.frame_id = '';
      }
      if (initObj.hasOwnProperty('polyfitLanes')) {
        this.polyfitLanes = initObj.polyfitLanes
      }
      else {
        this.polyfitLanes = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PolyfitLaneDataArray
    // Serialize message field [frame_id]
    bufferOffset = _serializer.string(obj.frame_id, buffer, bufferOffset);
    // Serialize message field [polyfitLanes]
    // Serialize the length for message field [polyfitLanes]
    bufferOffset = _serializer.uint32(obj.polyfitLanes.length, buffer, bufferOffset);
    obj.polyfitLanes.forEach((val) => {
      bufferOffset = PolyfitLaneData.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PolyfitLaneDataArray
    let len;
    let data = new PolyfitLaneDataArray(null);
    // Deserialize message field [frame_id]
    data.frame_id = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [polyfitLanes]
    // Deserialize array length for message field [polyfitLanes]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.polyfitLanes = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.polyfitLanes[i] = PolyfitLaneData.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.frame_id);
    object.polyfitLanes.forEach((val) => {
      length += PolyfitLaneData.getMessageSize(val);
    });
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autonomous_msg/PolyfitLaneDataArray';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1c4f872af1e86d670a3cbaed9d3c5647';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string frame_id
    PolyfitLaneData[] polyfitLanes
    ================================================================================
    MSG: autonomous_msg/PolyfitLaneData
    string frame_id
    string id 
    float64 a0
    float64 a1
    float64 a2
    float64 a3
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PolyfitLaneDataArray(null);
    if (msg.frame_id !== undefined) {
      resolved.frame_id = msg.frame_id;
    }
    else {
      resolved.frame_id = ''
    }

    if (msg.polyfitLanes !== undefined) {
      resolved.polyfitLanes = new Array(msg.polyfitLanes.length);
      for (let i = 0; i < resolved.polyfitLanes.length; ++i) {
        resolved.polyfitLanes[i] = PolyfitLaneData.Resolve(msg.polyfitLanes[i]);
      }
    }
    else {
      resolved.polyfitLanes = []
    }

    return resolved;
    }
};

module.exports = PolyfitLaneDataArray;
