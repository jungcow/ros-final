;; Auto-generated. Do not edit!


(when (boundp 'autonomous_msg::PointWithArclength)
  (if (not (find-package "AUTONOMOUS_MSG"))
    (make-package "AUTONOMOUS_MSG"))
  (shadow 'PointWithArclength (find-package "AUTONOMOUS_MSG")))
(unless (find-package "AUTONOMOUS_MSG::POINTWITHARCLENGTH")
  (make-package "AUTONOMOUS_MSG::POINTWITHARCLENGTH"))

(in-package "ROS")
;;//! \htmlinclude PointWithArclength.msg.html


(defclass autonomous_msg::PointWithArclength
  :super ros::object
  :slots (_x _y _arclength ))

(defmethod autonomous_msg::PointWithArclength
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:arclength __arclength) 0.0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _arclength (float __arclength))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:arclength
   (&optional __arclength)
   (if __arclength (setq _arclength __arclength)) _arclength)
  (:serialization-length
   ()
   (+
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _arclength
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _arclength
       (sys::poke _arclength (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _arclength
     (setq _arclength (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get autonomous_msg::PointWithArclength :md5sum-) "c506beb715b61f42d987dcfd7000dedb")
(setf (get autonomous_msg::PointWithArclength :datatype-) "autonomous_msg/PointWithArclength")
(setf (get autonomous_msg::PointWithArclength :definition-)
      "float64 x
float64 y
float64 arclength
")



(provide :autonomous_msg/PointWithArclength "c506beb715b61f42d987dcfd7000dedb")


