;; Auto-generated. Do not edit!


(when (boundp 'autonomous_msg::LanePointData)
  (if (not (find-package "AUTONOMOUS_MSG"))
    (make-package "AUTONOMOUS_MSG"))
  (shadow 'LanePointData (find-package "AUTONOMOUS_MSG")))
(unless (find-package "AUTONOMOUS_MSG::LANEPOINTDATA")
  (make-package "AUTONOMOUS_MSG::LANEPOINTDATA"))

(in-package "ROS")
;;//! \htmlinclude LanePointData.msg.html


(defclass autonomous_msg::LanePointData
  :super ros::object
  :slots (_frame_id _id _point ))

(defmethod autonomous_msg::LanePointData
  (:init
   (&key
    ((:frame_id __frame_id) "")
    ((:id __id) "")
    ((:point __point) ())
    )
   (send-super :init)
   (setq _frame_id (string __frame_id))
   (setq _id (string __id))
   (setq _point __point)
   self)
  (:frame_id
   (&optional __frame_id)
   (if __frame_id (setq _frame_id __frame_id)) _frame_id)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:point
   (&rest __point)
   (if (keywordp (car __point))
       (send* _point __point)
     (progn
       (if __point (setq _point (car __point)))
       _point)))
  (:serialization-length
   ()
   (+
    ;; string _frame_id
    4 (length _frame_id)
    ;; string _id
    4 (length _id)
    ;; autonomous_msg/PointWithArclength[] _point
    (apply #'+ (send-all _point :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _frame_id
       (write-long (length _frame_id) s) (princ _frame_id s)
     ;; string _id
       (write-long (length _id) s) (princ _id s)
     ;; autonomous_msg/PointWithArclength[] _point
     (write-long (length _point) s)
     (dolist (elem _point)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _frame_id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _frame_id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; autonomous_msg/PointWithArclength[] _point
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _point (let (r) (dotimes (i n) (push (instance autonomous_msg::PointWithArclength :init) r)) r))
     (dolist (elem- _point)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get autonomous_msg::LanePointData :md5sum-) "bcc833df10bd61adf00504adcdbf2635")
(setf (get autonomous_msg::LanePointData :datatype-) "autonomous_msg/LanePointData")
(setf (get autonomous_msg::LanePointData :definition-)
      "string frame_id
string id 
autonomous_msg/PointWithArclength[] point
================================================================================
MSG: autonomous_msg/PointWithArclength
float64 x
float64 y
float64 arclength
")



(provide :autonomous_msg/LanePointData "bcc833df10bd61adf00504adcdbf2635")


