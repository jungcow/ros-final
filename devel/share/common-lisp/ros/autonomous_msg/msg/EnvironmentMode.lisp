; Auto-generated. Do not edit!


(cl:in-package autonomous_msg-msg)


;//! \htmlinclude EnvironmentMode.msg.html

(cl:defclass <EnvironmentMode> (roslisp-msg-protocol:ros-message)
  ((ice_mode
    :reader ice_mode
    :initarg :ice_mode
    :type cl:string
    :initform "")
   (hill_mode
    :reader hill_mode
    :initarg :hill_mode
    :type cl:string
    :initform ""))
)

(cl:defclass EnvironmentMode (<EnvironmentMode>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <EnvironmentMode>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'EnvironmentMode)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name autonomous_msg-msg:<EnvironmentMode> is deprecated: use autonomous_msg-msg:EnvironmentMode instead.")))

(cl:ensure-generic-function 'ice_mode-val :lambda-list '(m))
(cl:defmethod ice_mode-val ((m <EnvironmentMode>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autonomous_msg-msg:ice_mode-val is deprecated.  Use autonomous_msg-msg:ice_mode instead.")
  (ice_mode m))

(cl:ensure-generic-function 'hill_mode-val :lambda-list '(m))
(cl:defmethod hill_mode-val ((m <EnvironmentMode>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autonomous_msg-msg:hill_mode-val is deprecated.  Use autonomous_msg-msg:hill_mode instead.")
  (hill_mode m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <EnvironmentMode>) ostream)
  "Serializes a message object of type '<EnvironmentMode>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'ice_mode))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'ice_mode))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'hill_mode))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'hill_mode))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <EnvironmentMode>) istream)
  "Deserializes a message object of type '<EnvironmentMode>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'ice_mode) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'ice_mode) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'hill_mode) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'hill_mode) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<EnvironmentMode>)))
  "Returns string type for a message object of type '<EnvironmentMode>"
  "autonomous_msg/EnvironmentMode")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'EnvironmentMode)))
  "Returns string type for a message object of type 'EnvironmentMode"
  "autonomous_msg/EnvironmentMode")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<EnvironmentMode>)))
  "Returns md5sum for a message object of type '<EnvironmentMode>"
  "df53af7b00c9079615c2b52e2721e823")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'EnvironmentMode)))
  "Returns md5sum for a message object of type 'EnvironmentMode"
  "df53af7b00c9079615c2b52e2721e823")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<EnvironmentMode>)))
  "Returns full string definition for message of type '<EnvironmentMode>"
  (cl:format cl:nil "string ice_mode~%string hill_mode~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'EnvironmentMode)))
  "Returns full string definition for message of type 'EnvironmentMode"
  (cl:format cl:nil "string ice_mode~%string hill_mode~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <EnvironmentMode>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'ice_mode))
     4 (cl:length (cl:slot-value msg 'hill_mode))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <EnvironmentMode>))
  "Converts a ROS message object to a list"
  (cl:list 'EnvironmentMode
    (cl:cons ':ice_mode (ice_mode msg))
    (cl:cons ':hill_mode (hill_mode msg))
))
