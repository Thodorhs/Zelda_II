
#include "Configurator.h"
#include <map>





template < class T >
class base_creator
{
public:
	virtual T* create() = 0;
	
};

	template < class derived_type, class base_type >
	class config_creator : base_creator<base_type> {
	public:
		base_type* create()  override {
			return new derived_type();
		}
	};

	template <class derived_type, class base_type >
	class factory
	{
	public:
		void register_type(configurators_t id, config_creator<derived_type,base_type>* _fn)
		{
			_function_map[id] = _fn;
		}

		base_type* create(int id)
		{
			return _function_map[id]->create();
		}

	private:
		std::map<int, config_creator<derived_type,base_type>*> _function_map;
	};


	

