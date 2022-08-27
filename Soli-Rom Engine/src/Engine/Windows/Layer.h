#pragma once

namespace SoliRom
{
	class Layer
	{
	public:
		Layer(std::string _name);
		virtual ~Layer() = default;

		virtual void onUpdate() {}

		virtual void onEvent() {}

	private:
		std::string name;
	};
}


