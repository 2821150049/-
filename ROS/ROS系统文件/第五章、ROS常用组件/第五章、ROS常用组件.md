# 第五章、ROS常用组件

## 一、TF常用组件

### 1.坐标系位置关系

*geometry_msgs/TransformStamped*：坐标系位置关系

```C++
std_msgs/Header header                     #头信息
  uint32 seq                               #|-- 序列号
  time stamp                               #|-- 时间戳
  string frame_id                          #|-- 基坐标名称
string child_frame_id                      #子坐标的名称
geometry_msgs/Transform transform          #坐标信息
  geometry_msgs/Vector3 translation        #偏移量
    float64 x                              #|-- X 方向的偏移量
    float64 y                              #|-- Y 方向的偏移量
    float64 z                              #|-- Z 方向上的偏移量
  geometry_msgs/Quaternion rotation        #四元数
    float64 x
    float64 y
    float64 z
    float64 w
```

### 2.坐标点位置关系

*geometry_msgs/PointStamped*：坐标点的位置信息

```C++
std_msgs/Header header
  uint32 seq	#|-- 序列号
  time stamp	#|-- 时间戳
  string frame_id   #以那个坐标系为参考物的
geometry_msgs/Point point 	#具体的坐标位置
  float64 x
  float64 y
  float64 z
```

### 3.坐标发布.h文件

*发布方：*

```C++
#include "ros/ros.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2_msgs/TFMessage.h"  
namespace tf2_ros
{
    class StaticTransformBroadcaster{
        public:
        StaticTransformBroadcaster();
        void sendTransform(const geometry_msgs::TransformStamped & transform) {
            sendTransform(std::vector<geometry_msgs::TransformStamped>({transform}));
        }
        void sendTransform(const std::vector<geometry_msgs::TransformStamped> & transforms);
        private:
        ros::NodeHandle node_;
        ros::Publisher publisher_;
        tf2_msgs::TFMessage net_message_;
    };
}
#endif //TF_STATICTRANSFORMBROADCASTER_H
-------------------------------------------------------------------
 #ifndef TF2_ROS_TRANSFORMBROADCASTER_H
 #define TF2_ROS_TRANSFORMBROADCASTER_H
 #include "ros/ros.h"
 #include "geometry_msgs/TransformStamped.h"
 namespace tf2_ros
 {
 class TransformBroadcaster{
 public:
   TransformBroadcaster();
   //  void sendTransform(const StampedTransform & transform);
   //  void sendTransform(const std::vector<StampedTransform> & transforms);
   void sendTransform(const geometry_msgs::TransformStamped & transform);
   void sendTransform(const std::vector<geometry_msgs::TransformStamped> & transforms);
 private:
   ros::NodeHandle node_;
   ros::Publisher publisher_;
 };
 }
 #endif //TF_TRANSFORMBROADCASTER_H
----------------------------------------------------------------
/*
	用途：发送坐标系位置关系消息
	参数：位置坐标系位置信息
		消息类型：geometry_msgs::TransformStamped（包含在头文件geometry_msgs/TransformStamped.h中）
	包含头文件：	static_transform_broadcaster.h
	用法：
		创建一个tf2_ros::StaticTransformBroadcaster对象
		tf2_ros::StaticTransformBroadcaster tf_pub;
		组织发布的消息
		geometry_msgs::TransformStamped tfs;
		发送坐标信息
		tf_pub.sendTransform(tfs);
*/
void tf2_ros::StaticTransformBroadcaster::sendTransform(const geometry_msgs::TransformStamped &transform)	
---------------------------------------------------------------
    
```

四元数头文件：

[坐标变换]: http://docs.ros.org/en/noetic/api/tf2/html/Quaternion_8h.html

*订阅方*

*buffer.h*

```C++
 #ifndef TF2_ROS_BUFFER_H
 #define TF2_ROS_BUFFER_H
 #include <tf2_ros/buffer_interface.h>
 #include <tf2/buffer_core.h>
 #include <tf2_msgs/FrameGraph.h>
 #include <ros/ros.h>
 #include <tf2/convert.h>
 namespace tf2_ros
 {
   class Buffer: public BufferInterface, public tf2::BufferCore
   {
   public:
     using tf2::BufferCore::lookupTransform;
     using tf2::BufferCore::canTransform;
     Buffer(ros::Duration cache_time = ros::Duration(BufferCore::DEFAULT_CACHE_TIME), bool debug = false);
     virtual geometry_msgs::TransformStamped 
     lookupTransform(const std::string& target_frame, const std::string& source_frame,
                     const ros::Time& time, const ros::Duration timeout) const;
     virtual geometry_msgs::TransformStamped 
     lookupTransform(const std::string& target_frame, const ros::Time& target_time,
                     const std::string& source_frame, const ros::Time& source_time,
                     const std::string& fixed_frame, const ros::Duration timeout) const;
  
  
     virtual bool
     canTransform(const std::string& target_frame, const std::string& source_frame, 
                  const ros::Time& target_time, const ros::Duration timeout, std::string* errstr = NULL) const;
     virtual bool
       canTransform(const std::string& target_frame, const ros::Time& target_time,
                    const std::string& source_frame, const ros::Time& source_time,
                    const std::string& fixed_frame, const ros::Duration timeout, std::string* errstr = NULL) const; 
   private:
     bool getFrames(tf2_msgs::FrameGraph::Request& req, tf2_msgs::FrameGraph::Response& res) ;
     // conditionally error if dedicated_thread unset.
     bool checkAndErrorDedicatedThreadPresent(std::string* errstr) const;
     ros::ServiceServer frames_server_;
   }; // class 
 static const std::string threading_error = "Do not call canTransform or lookupTransform with a timeout unless you are using another thread for populating data. Without a dedicated thread it will always timeout.  If you have a separate thread servicing tf messages, call setUsingDedicatedThread(true) on your Buffer instance."; 
 } // namespace
 #endif // TF2_ROS_BUFFER_H
```

***transform_listener.h***

```c++
#ifndef TF2_ROS_TRANSFORMLISTENER_H
 #define TF2_ROS_TRANSFORMLISTENER_H
  
 #include "std_msgs/Empty.h"
 #include "tf2_msgs/TFMessage.h"
 #include "ros/ros.h"
 #include "ros/callback_queue.h"
 #include "tf2_ros/buffer.h"
 #include "boost/thread.hpp"
 namespace tf2_ros{
 class TransformListener
 {
 public:
   TransformListener(tf2::BufferCore& buffer, bool spin_thread = true,
       ros::TransportHints transport_hints = ros::TransportHints());
   TransformListener(tf2::BufferCore& buffer, const ros::NodeHandle& nh, bool spin_thread = true,
       ros::TransportHints transport_hints = ros::TransportHints());
   ~TransformListener();
 private:
   void init();
   void initWithThread();
   void subscription_callback(const ros::MessageEvent<tf2_msgs::TFMessage const>& msg_evt);
   void static_subscription_callback(const ros::MessageEvent<tf2_msgs::TFMessage const>& msg_evt);
   void subscription_callback_impl(const ros::MessageEvent<tf2_msgs::TFMessage const>& msg_evt, bool is_static);
   ros::CallbackQueue tf_message_callback_queue_;
   boost::thread* dedicated_listener_thread_;
   ros::NodeHandle node_;
   ros::Subscriber message_subscriber_tf_;
   ros::Subscriber message_subscriber_tf_static_;
   tf2::BufferCore& buffer_;
   bool using_dedicated_thread_;
   ros::TransportHints transport_hints_;
   ros::Time last_update_;
   void dedicatedListenerThread()
   {
     while (using_dedicated_thread_)
     {
tf_message_callback_queue_.callAvailable(ros::WallDuration(0.01));
     }
   };
 };
 }
 #endif //TF_TRANSFORMLISTENER_H
```

*坐标点转换*

