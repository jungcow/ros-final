;; Auto-generated. Do not edit!


(when (boundp 'autonomous_msg::VehicleOutputs)
  (if (not (find-package "AUTONOMOUS_MSG"))
    (make-package "AUTONOMOUS_MSG"))
  (shadow 'VehicleOutputs (find-package "AUTONOMOUS_MSG")))
(unless (find-package "AUTONOMOUS_MSG::VEHICLEOUTPUTS")
  (make-package "AUTONOMOUS_MSG::VEHICLEOUTPUTS"))

(in-package "ROS")
;;//! \htmlinclude VehicleOutputs.msg.html


(defclass autonomous_msg::VehicleOutputs
  :super ros::object
  :slots (_vehicleOuputs ))

(defmethod autonomous_msg::VehicleOutputs
  (:init
   (&key
    ((:vehicleOuputs __vehicleOuputs) ())
    )
   (send-super :init)
   (setq _vehicleOuputs __vehicleOuputs)
   self)
  (:vehicleOuputs
   (&rest __vehicleOuputs)
   (if (keywordp (car __vehicleOuputs))
       (send* _vehicleOuputs __vehicleOuputs)
     (progn
       (if __vehicleOuputs (setq _vehicleOuputs (car __vehicleOuputs)))
       _vehicleOuputs)))
  (:serialization-length
   ()
   (+
    ;; autonomous_msg/VehicleOutput[] _vehicleOuputs
    (apply #'+ (send-all _vehicleOuputs :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; autonomous_msg/VehicleOutput[] _vehicleOuputs
     (write-long (length _vehicleOuputs) s)
     (dolist (elem _vehicleOuputs)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; autonomous_msg/VehicleOutput[] _vehicleOuputs
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _vehicleOuputs (let (r) (dotimes (i n) (push (instance autonomous_msg::VehicleOutput :init) r)) r))
     (dolist (elem- _vehicleOuputs)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get autonomous_msg::VehicleOutputs :md5sum-) "1f3e123ab591600bc0713eeba94ade0a")
(setf (get autonomous_msg::VehicleOutputs :datatype-) "autonomous_msg/VehicleOutputs")
(setf (get autonomous_msg::VehicleOutputs :definition-)
      "VehicleOutput[] vehicleOuputs
================================================================================
MSG: autonomous_msg/VehicleOutput
string id 
float64 x
float64 y
float64 yaw
float64 velocity
float64 length
float64 width
")



(provide :autonomous_msg/VehicleOutputs "1f3e123ab591600bc0713eeba94ade0a")


