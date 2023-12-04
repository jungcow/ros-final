;; Auto-generated. Do not edit!


(when (boundp 'autonomous_msg::EnvironmentParam)
  (if (not (find-package "AUTONOMOUS_MSG"))
    (make-package "AUTONOMOUS_MSG"))
  (shadow 'EnvironmentParam (find-package "AUTONOMOUS_MSG")))
(unless (find-package "AUTONOMOUS_MSG::ENVIRONMENTPARAM")
  (make-package "AUTONOMOUS_MSG::ENVIRONMENTPARAM"))

(in-package "ROS")
;;//! \htmlinclude EnvironmentParam.msg.html


(defclass autonomous_msg::EnvironmentParam
  :super ros::object
  :slots (_fyf_max _fyr_max _slope_angle ))

(defmethod autonomous_msg::EnvironmentParam
  (:init
   (&key
    ((:fyf_max __fyf_max) 0.0)
    ((:fyr_max __fyr_max) 0.0)
    ((:slope_angle __slope_angle) 0.0)
    )
   (send-super :init)
   (setq _fyf_max (float __fyf_max))
   (setq _fyr_max (float __fyr_max))
   (setq _slope_angle (float __slope_angle))
   self)
  (:fyf_max
   (&optional __fyf_max)
   (if __fyf_max (setq _fyf_max __fyf_max)) _fyf_max)
  (:fyr_max
   (&optional __fyr_max)
   (if __fyr_max (setq _fyr_max __fyr_max)) _fyr_max)
  (:slope_angle
   (&optional __slope_angle)
   (if __slope_angle (setq _slope_angle __slope_angle)) _slope_angle)
  (:serialization-length
   ()
   (+
    ;; float64 _fyf_max
    8
    ;; float64 _fyr_max
    8
    ;; float64 _slope_angle
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _fyf_max
       (sys::poke _fyf_max (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _fyr_max
       (sys::poke _fyr_max (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _slope_angle
       (sys::poke _slope_angle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _fyf_max
     (setq _fyf_max (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _fyr_max
     (setq _fyr_max (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _slope_angle
     (setq _slope_angle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get autonomous_msg::EnvironmentParam :md5sum-) "f757b3e255dfef4f680d3558f78ceb06")
(setf (get autonomous_msg::EnvironmentParam :datatype-) "autonomous_msg/EnvironmentParam")
(setf (get autonomous_msg::EnvironmentParam :definition-)
      "float64 fyf_max
float64 fyr_max
float64 slope_angle
")



(provide :autonomous_msg/EnvironmentParam "f757b3e255dfef4f680d3558f78ceb06")


