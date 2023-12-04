; Auto-generated. Do not edit!


(cl:in-package autonomous_msg-msg)


;//! \htmlinclude EnvironmentDetected.msg.html

(cl:defclass <EnvironmentDetected> (roslisp-msg-protocol:ros-message)
  ((ice_param
    :reader ice_param
    :initarg :ice_param
    :type cl:float
    :initform 0.0)
   (ice_mode
    :reader ice_mode
    :initarg :ice_mode
    :type cl:string
    :initform ""))
)

(cl:defclass EnvironmentDetected (<EnvironmentDetected>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <EnvironmentDetected>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'EnvironmentDetected)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name autonomous_msg-msg:<EnvironmentDetected> is deprecated: use autonomous_msg-msg:EnvironmentDetected instead.")))

(cl:ensure-generic-function 'ice_param-val :lambda-list '(m))
(cl:defmethod ice_param-val ((m <EnvironmentDetected>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autonomous_msg-msg:ice_param-val is deprecated.  Use autonomous_msg-msg:ice_param instead.")
  (ice_param m))

(cl:ensure-generic-function 'ice_mode-val :lambda-list '(m))
(cl:defmethod ice_mode-val ((m <EnvironmentDetected>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autonomous_msg-msg:ice_mode-val is deprecated.  Use autonomous_msg-msg:ice_mode instead.")
  (ice_mode m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <EnvironmentDetected>) ostream)
  "Serializes a message object of type '<EnvironmentDetected>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'ice_param))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'ice_mode))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'ice_mode))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <EnvironmentDetected>) istream)
  "Deserializes a message object of type '<EnvironmentDetected>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ice_param) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'ice_mode) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'ice_mode) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<EnvironmentDetected>)))
  "Returns string type for a message object of type '<EnvironmentDetected>"
  "autonomous_msg/EnvironmentDetected")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'EnvironmentDetected)))
  "Returns string type for a message object of type 'EnvironmentDetected"
  "autonomous_msg/EnvironmentDetected")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<EnvironmentDetected>)))
  "Returns md5sum for a message object of type '<EnvironmentDetected>"
  "57850e5a040808185fbe00e153e12c75")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'EnvironmentDetected)))
  "Returns md5sum for a message object of type 'EnvironmentDetected"
  "57850e5a040808185fbe00e153e12c75")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<EnvironmentDetected>)))
  "Returns full string definition for message of type '<EnvironmentDetected>"
  (cl:format cl:nil "float64 ice_param~%string ice_mode~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'EnvironmentDetected)))
  "Returns full string definition for message of type 'EnvironmentDetected"
  (cl:format cl:nil "float64 ice_param~%string ice_mode~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <EnvironmentDetected>))
  (cl:+ 0
     8
     4 (cl:length (cl:slot-value msg 'ice_mode))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <EnvironmentDetected>))
  "Converts a ROS message object to a list"
  (cl:list 'EnvironmentDetected
    (cl:cons ':ice_param (ice_param msg))
    (cl:cons ':ice_mode (ice_mode msg))
))
