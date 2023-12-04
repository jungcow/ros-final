; Auto-generated. Do not edit!


(cl:in-package autonomous_msg-msg)


;//! \htmlinclude VehicleOutputs.msg.html

(cl:defclass <VehicleOutputs> (roslisp-msg-protocol:ros-message)
  ((vehicleOuputs
    :reader vehicleOuputs
    :initarg :vehicleOuputs
    :type (cl:vector autonomous_msg-msg:VehicleOutput)
   :initform (cl:make-array 0 :element-type 'autonomous_msg-msg:VehicleOutput :initial-element (cl:make-instance 'autonomous_msg-msg:VehicleOutput))))
)

(cl:defclass VehicleOutputs (<VehicleOutputs>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VehicleOutputs>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VehicleOutputs)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name autonomous_msg-msg:<VehicleOutputs> is deprecated: use autonomous_msg-msg:VehicleOutputs instead.")))

(cl:ensure-generic-function 'vehicleOuputs-val :lambda-list '(m))
(cl:defmethod vehicleOuputs-val ((m <VehicleOutputs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autonomous_msg-msg:vehicleOuputs-val is deprecated.  Use autonomous_msg-msg:vehicleOuputs instead.")
  (vehicleOuputs m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VehicleOutputs>) ostream)
  "Serializes a message object of type '<VehicleOutputs>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'vehicleOuputs))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'vehicleOuputs))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VehicleOutputs>) istream)
  "Deserializes a message object of type '<VehicleOutputs>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'vehicleOuputs) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'vehicleOuputs)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'autonomous_msg-msg:VehicleOutput))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VehicleOutputs>)))
  "Returns string type for a message object of type '<VehicleOutputs>"
  "autonomous_msg/VehicleOutputs")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VehicleOutputs)))
  "Returns string type for a message object of type 'VehicleOutputs"
  "autonomous_msg/VehicleOutputs")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VehicleOutputs>)))
  "Returns md5sum for a message object of type '<VehicleOutputs>"
  "1f3e123ab591600bc0713eeba94ade0a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VehicleOutputs)))
  "Returns md5sum for a message object of type 'VehicleOutputs"
  "1f3e123ab591600bc0713eeba94ade0a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VehicleOutputs>)))
  "Returns full string definition for message of type '<VehicleOutputs>"
  (cl:format cl:nil "VehicleOutput[] vehicleOuputs~%================================================================================~%MSG: autonomous_msg/VehicleOutput~%string id ~%float64 x~%float64 y~%float64 yaw~%float64 velocity~%float64 length~%float64 width~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VehicleOutputs)))
  "Returns full string definition for message of type 'VehicleOutputs"
  (cl:format cl:nil "VehicleOutput[] vehicleOuputs~%================================================================================~%MSG: autonomous_msg/VehicleOutput~%string id ~%float64 x~%float64 y~%float64 yaw~%float64 velocity~%float64 length~%float64 width~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VehicleOutputs>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'vehicleOuputs) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VehicleOutputs>))
  "Converts a ROS message object to a list"
  (cl:list 'VehicleOutputs
    (cl:cons ':vehicleOuputs (vehicleOuputs msg))
))
