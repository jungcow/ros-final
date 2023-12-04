// Auto-generated. Do not edit!

// (in-package autonomous_msg.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let VehicleOutput = require('./VehicleOutput.js');

//-----------------------------------------------------------

class VehicleOutputs {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.vehicleOuputs = null;
    }
    else {
      if (initObj.hasOwnProperty('vehicleOuputs')) {
        this.vehicleOuputs = initObj.vehicleOuputs
      }
      else {
        this.vehicleOuputs = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VehicleOutputs
    // Serialize message field [vehicleOuputs]
    // Serialize the length for message field [vehicleOuputs]
    bufferOffset = _serializer.uint32(obj.vehicleOuputs.length, buffer, bufferOffset);
    obj.vehicleOuputs.forEach((val) => {
      bufferOffset = VehicleOutput.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VehicleOutputs
    let len;
    let data = new VehicleOutputs(null);
    // Deserialize message field [vehicleOuputs]
    // Deserialize array length for message field [vehicleOuputs]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.vehicleOuputs = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.vehicleOuputs[i] = VehicleOutput.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.vehicleOuputs.forEach((val) => {
      length += VehicleOutput.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autonomous_msg/VehicleOutputs';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1f3e123ab591600bc0713eeba94ade0a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    VehicleOutput[] vehicleOuputs
    ================================================================================
    MSG: autonomous_msg/VehicleOutput
    string id 
    float64 x
    float64 y
    float64 yaw
    float64 velocity
    float64 length
    float64 width
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new VehicleOutputs(null);
    if (msg.vehicleOuputs !== undefined) {
      resolved.vehicleOuputs = new Array(msg.vehicleOuputs.length);
      for (let i = 0; i < resolved.vehicleOuputs.length; ++i) {
        resolved.vehicleOuputs[i] = VehicleOutput.Resolve(msg.vehicleOuputs[i]);
      }
    }
    else {
      resolved.vehicleOuputs = []
    }

    return resolved;
    }
};

module.exports = VehicleOutputs;
