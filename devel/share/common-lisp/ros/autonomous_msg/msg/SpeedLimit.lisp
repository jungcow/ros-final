; Auto-generated. Do not edit!


(cl:in-package autonomous_msg-msg)


;//! \htmlinclude SpeedLimit.msg.html

(cl:defclass <SpeedLimit> (roslisp-msg-protocol:ros-message)
  ((curr_limit
    :reader curr_limit
    :initarg :curr_limit
    :type cl:float
    :initform 0.0)
   (next_limit
    :reader next_limit
    :initarg :next_limit
    :type cl:float
    :initform 0.0)
   (dist_left
    :reader dist_left
    :initarg :dist_left
    :type cl:float
    :initform 0.0))
)

(cl:defclass SpeedLimit (<SpeedLimit>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SpeedLimit>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SpeedLimit)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name autonomous_msg-msg:<SpeedLimit> is deprecated: use autonomous_msg-msg:SpeedLimit instead.")))

(cl:ensure-generic-function 'curr_limit-val :lambda-list '(m))
(cl:defmethod curr_limit-val ((m <SpeedLimit>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autonomous_msg-msg:curr_limit-val is deprecated.  Use autonomous_msg-msg:curr_limit instead.")
  (curr_limit m))

(cl:ensure-generic-function 'next_limit-val :lambda-list '(m))
(cl:defmethod next_limit-val ((m <SpeedLimit>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autonomous_msg-msg:next_limit-val is deprecated.  Use autonomous_msg-msg:next_limit instead.")
  (next_limit m))

(cl:ensure-generic-function 'dist_left-val :lambda-list '(m))
(cl:defmethod dist_left-val ((m <SpeedLimit>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autonomous_msg-msg:dist_left-val is deprecated.  Use autonomous_msg-msg:dist_left instead.")
  (dist_left m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SpeedLimit>) ostream)
  "Serializes a message object of type '<SpeedLimit>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'curr_limit))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'next_limit))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'dist_left))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SpeedLimit>) istream)
  "Deserializes a message object of type '<SpeedLimit>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'curr_limit) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'next_limit) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dist_left) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SpeedLimit>)))
  "Returns string type for a message object of type '<SpeedLimit>"
  "autonomous_msg/SpeedLimit")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SpeedLimit)))
  "Returns string type for a message object of type 'SpeedLimit"
  "autonomous_msg/SpeedLimit")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SpeedLimit>)))
  "Returns md5sum for a message object of type '<SpeedLimit>"
  "6811f8ec87f49f482a9d61cafc2ca244")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SpeedLimit)))
  "Returns md5sum for a message object of type 'SpeedLimit"
  "6811f8ec87f49f482a9d61cafc2ca244")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SpeedLimit>)))
  "Returns full string definition for message of type '<SpeedLimit>"
  (cl:format cl:nil "float64 curr_limit~%float64 next_limit~%float64 dist_left~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SpeedLimit)))
  "Returns full string definition for message of type 'SpeedLimit"
  (cl:format cl:nil "float64 curr_limit~%float64 next_limit~%float64 dist_left~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SpeedLimit>))
  (cl:+ 0
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SpeedLimit>))
  "Converts a ROS message object to a list"
  (cl:list 'SpeedLimit
    (cl:cons ':curr_limit (curr_limit msg))
    (cl:cons ':next_limit (next_limit msg))
    (cl:cons ':dist_left (dist_left msg))
))
