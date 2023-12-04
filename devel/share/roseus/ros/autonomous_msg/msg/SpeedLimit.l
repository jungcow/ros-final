;; Auto-generated. Do not edit!


(when (boundp 'autonomous_msg::SpeedLimit)
  (if (not (find-package "AUTONOMOUS_MSG"))
    (make-package "AUTONOMOUS_MSG"))
  (shadow 'SpeedLimit (find-package "AUTONOMOUS_MSG")))
(unless (find-package "AUTONOMOUS_MSG::SPEEDLIMIT")
  (make-package "AUTONOMOUS_MSG::SPEEDLIMIT"))

(in-package "ROS")
;;//! \htmlinclude SpeedLimit.msg.html


(defclass autonomous_msg::SpeedLimit
  :super ros::object
  :slots (_curr_limit _next_limit _dist_left ))

(defmethod autonomous_msg::SpeedLimit
  (:init
   (&key
    ((:curr_limit __curr_limit) 0.0)
    ((:next_limit __next_limit) 0.0)
    ((:dist_left __dist_left) 0.0)
    )
   (send-super :init)
   (setq _curr_limit (float __curr_limit))
   (setq _next_limit (float __next_limit))
   (setq _dist_left (float __dist_left))
   self)
  (:curr_limit
   (&optional __curr_limit)
   (if __curr_limit (setq _curr_limit __curr_limit)) _curr_limit)
  (:next_limit
   (&optional __next_limit)
   (if __next_limit (setq _next_limit __next_limit)) _next_limit)
  (:dist_left
   (&optional __dist_left)
   (if __dist_left (setq _dist_left __dist_left)) _dist_left)
  (:serialization-length
   ()
   (+
    ;; float64 _curr_limit
    8
    ;; float64 _next_limit
    8
    ;; float64 _dist_left
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _curr_limit
       (sys::poke _curr_limit (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _next_limit
       (sys::poke _next_limit (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _dist_left
       (sys::poke _dist_left (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _curr_limit
     (setq _curr_limit (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _next_limit
     (setq _next_limit (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _dist_left
     (setq _dist_left (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get autonomous_msg::SpeedLimit :md5sum-) "6811f8ec87f49f482a9d61cafc2ca244")
(setf (get autonomous_msg::SpeedLimit :datatype-) "autonomous_msg/SpeedLimit")
(setf (get autonomous_msg::SpeedLimit :definition-)
      "float64 curr_limit
float64 next_limit
float64 dist_left
")



(provide :autonomous_msg/SpeedLimit "6811f8ec87f49f482a9d61cafc2ca244")


