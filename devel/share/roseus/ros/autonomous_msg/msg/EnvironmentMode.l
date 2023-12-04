;; Auto-generated. Do not edit!


(when (boundp 'autonomous_msg::EnvironmentMode)
  (if (not (find-package "AUTONOMOUS_MSG"))
    (make-package "AUTONOMOUS_MSG"))
  (shadow 'EnvironmentMode (find-package "AUTONOMOUS_MSG")))
(unless (find-package "AUTONOMOUS_MSG::ENVIRONMENTMODE")
  (make-package "AUTONOMOUS_MSG::ENVIRONMENTMODE"))

(in-package "ROS")
;;//! \htmlinclude EnvironmentMode.msg.html


(defclass autonomous_msg::EnvironmentMode
  :super ros::object
  :slots (_ice_mode _hill_mode ))

(defmethod autonomous_msg::EnvironmentMode
  (:init
   (&key
    ((:ice_mode __ice_mode) "")
    ((:hill_mode __hill_mode) "")
    )
   (send-super :init)
   (setq _ice_mode (string __ice_mode))
   (setq _hill_mode (string __hill_mode))
   self)
  (:ice_mode
   (&optional __ice_mode)
   (if __ice_mode (setq _ice_mode __ice_mode)) _ice_mode)
  (:hill_mode
   (&optional __hill_mode)
   (if __hill_mode (setq _hill_mode __hill_mode)) _hill_mode)
  (:serialization-length
   ()
   (+
    ;; string _ice_mode
    4 (length _ice_mode)
    ;; string _hill_mode
    4 (length _hill_mode)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _ice_mode
       (write-long (length _ice_mode) s) (princ _ice_mode s)
     ;; string _hill_mode
       (write-long (length _hill_mode) s) (princ _hill_mode s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _ice_mode
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _ice_mode (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _hill_mode
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _hill_mode (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get autonomous_msg::EnvironmentMode :md5sum-) "df53af7b00c9079615c2b52e2721e823")
(setf (get autonomous_msg::EnvironmentMode :datatype-) "autonomous_msg/EnvironmentMode")
(setf (get autonomous_msg::EnvironmentMode :definition-)
      "string ice_mode
string hill_mode
")



(provide :autonomous_msg/EnvironmentMode "df53af7b00c9079615c2b52e2721e823")


