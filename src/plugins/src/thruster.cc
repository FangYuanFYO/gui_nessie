#include <gazebo/gazebo.hh>
#include <gazebo/math/Pose.hh>
#include <gazebo/math/Vector3.hh>
#include <gazebo/physics/physics.hh>

namespace gazebo
{
	class ThrusterPlugin : public ModelPlugin
	{
		public: ThrusterPlugin() : ModelPlugin()
		{
			printf("ThrusterPlugin \n");
		}
		public: void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
		{
			math::Pose position;
			printf("ThrusterPlugin load !\n");
			position = _model->GetRelativePose();
			printf("Position : %f, %f, %f\n", position.pos.x, position.pos.y, position.pos.z);
		}
	};
	GZ_REGISTER_MODEL_PLUGIN(ThrusterPlugin)
}