; Auto-generated. Do not edit!


(cl:in-package autonomous_msg-msg)


;//! \htmlinclude EnvironmentParam.msg.html

(cl:defclass <EnvironmentParam> (roslisp-msg-protocol:ros-message)
  ((fyf_max
    :reader fyf_max
    :initarg :fyf_max
    :type cl:float
    :initform 0.0)
   (fyr_max
    :reader fyr_max
    :initarg :fyr_max
    :type cl:float
    :initform 0.0)
   (slope_angle
    :reader slope_angle
    :initarg :slope_angle
    :type cl:float
    :initform 0.0))
)

(cl:defclass EnvironmentParam (<EnvironmentParam>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <EnvironmentParam>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'EnvironmentParam)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name autonomous_msg-msg:<EnvironmentParam> is deprecated: use autonomous_msg-msg:EnvironmentParam instead.")))

(cl:ensure-generic-function 'fyf_max-val :lambda-list '(m))
(cl:defmethod fyf_max-val ((m <EnvironmentParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autonomous_msg-msg:fyf_max-val is deprecated.  Use autonomous_msg-msg:fyf_max instead.")
  (fyf_max m))

(cl:ensure-generic-function 'fyr_max-val :lambda-list '(m))
(cl:defmethod fyr_max-val ((m <EnvironmentParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autonomous_msg-msg:fyr_max-val is deprecated.  Use autonomous_msg-msg:fyr_max instead.")
  (fyr_max m))

(cl:ensure-generic-function 'slope_angle-val :lambda-list '(m))
(cl:defmethod slope_angle-val ((m <EnvironmentParam>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autonomous_msg-msg:slope_angle-val is deprecated.  Use autonomous_msg-msg:slope_angle instead.")
  (slope_angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <EnvironmentParam>) ostream)
  "Serializes a message object of type '<EnvironmentParam>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'fyf_max))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'fyr_max))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'slope_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <EnvironmentParam>) istream)
  "Deserializes a message object of type '<EnvironmentParam>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fyf_max) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fyr_max) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'slope_angle) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<EnvironmentParam>)))
  "Returns string type for a message object of type '<EnvironmentParam>"
  "autonomous_msg/EnvironmentParam")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'EnvironmentParam)))
  "Returns string type for a message object of type 'EnvironmentParam"
  "autonomous_msg/EnvironmentParam")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<EnvironmentParam>)))
  "Returns md5sum for a message object of type '<EnvironmentParam>"
  "f757b3e255dfef4f680d3558f78ceb06")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'EnvironmentParam)))
  "Returns md5sum for a message object of type 'EnvironmentParam"
  "f757b3e255dfef4f680d3558f78ceb06")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<EnvironmentParam>)))
  "Returns full string definition for message of type '<EnvironmentParam>"
  (cl:format cl:nil "float64 fyf_max~%float64 fyr_max~%float64 slope_angle~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'EnvironmentParam)))
  "Returns full string definition for message of type 'EnvironmentParam"
  (cl:format cl:nil "float64 fyf_max~%float64 fyr_max~%float64 slope_angle~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <EnvironmentParam>))
  (cl:+ 0
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <EnvironmentParam>))
  "Converts a ROS message object to a list"
  (cl:list 'EnvironmentParam
    (cl:cons ':fyf_max (fyf_max msg))
    (cl:cons ':fyr_max (fyr_max msg))
    (cl:cons ':slope_angle (slope_angle msg))
))
