;; Auto-generated. Do not edit!


(when (boundp 'autonomous_msg::EnvironmentDetected)
  (if (not (find-package "AUTONOMOUS_MSG"))
    (make-package "AUTONOMOUS_MSG"))
  (shadow 'EnvironmentDetected (find-package "AUTONOMOUS_MSG")))
(unless (find-package "AUTONOMOUS_MSG::ENVIRONMENTDETECTED")
  (make-package "AUTONOMOUS_MSG::ENVIRONMENTDETECTED"))

(in-package "ROS")
;;//! \htmlinclude EnvironmentDetected.msg.html


(defclass autonomous_msg::EnvironmentDetected
  :super ros::object
  :slots (_ice_param _ice_mode ))

(defmethod autonomous_msg::EnvironmentDetected
  (:init
   (&key
    ((:ice_param __ice_param) 0.0)
    ((:ice_mode __ice_mode) "")
    )
   (send-super :init)
   (setq _ice_param (float __ice_param))
   (setq _ice_mode (string __ice_mode))
   self)
  (:ice_param
   (&optional __ice_param)
   (if __ice_param (setq _ice_param __ice_param)) _ice_param)
  (:ice_mode
   (&optional __ice_mode)
   (if __ice_mode (setq _ice_mode __ice_mode)) _ice_mode)
  (:serialization-length
   ()
   (+
    ;; float64 _ice_param
    8
    ;; string _ice_mode
    4 (length _ice_mode)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _ice_param
       (sys::poke _ice_param (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; string _ice_mode
       (write-long (length _ice_mode) s) (princ _ice_mode s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _ice_param
     (setq _ice_param (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; string _ice_mode
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _ice_mode (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get autonomous_msg::EnvironmentDetected :md5sum-) "57850e5a040808185fbe00e153e12c75")
(setf (get autonomous_msg::EnvironmentDetected :datatype-) "autonomous_msg/EnvironmentDetected")
(setf (get autonomous_msg::EnvironmentDetected :definition-)
      "float64 ice_param
string ice_mode
")



(provide :autonomous_msg/EnvironmentDetected "57850e5a040808185fbe00e153e12c75")


