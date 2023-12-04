;; Auto-generated. Do not edit!


(when (boundp 'autonomous_msg::EnvironmentModeArea)
  (if (not (find-package "AUTONOMOUS_MSG"))
    (make-package "AUTONOMOUS_MSG"))
  (shadow 'EnvironmentModeArea (find-package "AUTONOMOUS_MSG")))
(unless (find-package "AUTONOMOUS_MSG::ENVIRONMENTMODEAREA")
  (make-package "AUTONOMOUS_MSG::ENVIRONMENTMODEAREA"))

(in-package "ROS")
;;//! \htmlinclude EnvironmentModeArea.msg.html


(defclass autonomous_msg::EnvironmentModeArea
  :super ros::object
  :slots (_ice_x _ice_y _ice_radius _hill_x _hill_y _hill_slope_angle ))

(defmethod autonomous_msg::EnvironmentModeArea
  (:init
   (&key
    ((:ice_x __ice_x) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:ice_y __ice_y) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:ice_radius __ice_radius) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:hill_x __hill_x) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:hill_y __hill_y) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:hill_slope_angle __hill_slope_angle) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _ice_x __ice_x)
   (setq _ice_y __ice_y)
   (setq _ice_radius __ice_radius)
   (setq _hill_x __hill_x)
   (setq _hill_y __hill_y)
   (setq _hill_slope_angle __hill_slope_angle)
   self)
  (:ice_x
   (&optional __ice_x)
   (if __ice_x (setq _ice_x __ice_x)) _ice_x)
  (:ice_y
   (&optional __ice_y)
   (if __ice_y (setq _ice_y __ice_y)) _ice_y)
  (:ice_radius
   (&optional __ice_radius)
   (if __ice_radius (setq _ice_radius __ice_radius)) _ice_radius)
  (:hill_x
   (&optional __hill_x)
   (if __hill_x (setq _hill_x __hill_x)) _hill_x)
  (:hill_y
   (&optional __hill_y)
   (if __hill_y (setq _hill_y __hill_y)) _hill_y)
  (:hill_slope_angle
   (&optional __hill_slope_angle)
   (if __hill_slope_angle (setq _hill_slope_angle __hill_slope_angle)) _hill_slope_angle)
  (:serialization-length
   ()
   (+
    ;; float64[] _ice_x
    (* 8    (length _ice_x)) 4
    ;; float64[] _ice_y
    (* 8    (length _ice_y)) 4
    ;; float64[] _ice_radius
    (* 8    (length _ice_radius)) 4
    ;; float64[] _hill_x
    (* 8    (length _hill_x)) 4
    ;; float64[] _hill_y
    (* 8    (length _hill_y)) 4
    ;; float64[] _hill_slope_angle
    (* 8    (length _hill_slope_angle)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[] _ice_x
     (write-long (length _ice_x) s)
     (dotimes (i (length _ice_x))
       (sys::poke (elt _ice_x i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _ice_y
     (write-long (length _ice_y) s)
     (dotimes (i (length _ice_y))
       (sys::poke (elt _ice_y i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _ice_radius
     (write-long (length _ice_radius) s)
     (dotimes (i (length _ice_radius))
       (sys::poke (elt _ice_radius i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _hill_x
     (write-long (length _hill_x) s)
     (dotimes (i (length _hill_x))
       (sys::poke (elt _hill_x i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _hill_y
     (write-long (length _hill_y) s)
     (dotimes (i (length _hill_y))
       (sys::poke (elt _hill_y i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _hill_slope_angle
     (write-long (length _hill_slope_angle) s)
     (dotimes (i (length _hill_slope_angle))
       (sys::poke (elt _hill_slope_angle i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[] _ice_x
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _ice_x (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _ice_x i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _ice_y
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _ice_y (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _ice_y i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _ice_radius
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _ice_radius (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _ice_radius i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _hill_x
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _hill_x (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _hill_x i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _hill_y
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _hill_y (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _hill_y i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _hill_slope_angle
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _hill_slope_angle (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _hill_slope_angle i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get autonomous_msg::EnvironmentModeArea :md5sum-) "aa04ea7b504bc5eedff12056d464548d")
(setf (get autonomous_msg::EnvironmentModeArea :datatype-) "autonomous_msg/EnvironmentModeArea")
(setf (get autonomous_msg::EnvironmentModeArea :definition-)
      "float64[] ice_x
float64[] ice_y
float64[] ice_radius
float64[] hill_x
float64[] hill_y
float64[] hill_slope_angle
")



(provide :autonomous_msg/EnvironmentModeArea "aa04ea7b504bc5eedff12056d464548d")


