#pragma once

namespace SoliRom
{
	class Layer
	{
	public:
		Layer(std::string _name);
		virtual ~Layer() = default;

		virtual void OnUpdate() {}

		virtual void OnEvent() {}

	private:
		std::string name;
	};
}


