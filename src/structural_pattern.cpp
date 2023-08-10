/*
 * C++ Design Patterns
 * Author: Jinta Zheng [https://github.com/jintazheng]
 *
 * Source code is licensed under MIT License
 * (for more details see LICENSE)
 *
 */

#include <iostream>
#include <vector>
/*
* The approached to assemble objects and classes into larger structures  (7 types).
*/
namespace structural_pattern {
	/* Adapter Pattern
	 * When to use the pattern?
	 *
	 * Use the Adapter pattern in the following situation:
	 *
	 * - When an existing class has interfaces that are not compatible with the ones you are using, and you need to use an adapter class to act as a converter.
	 * Examples:
	 * Your current API reads XML files (target class), but you want to use an API that reads JSON (service). You can create an adapter to convert from JSON to XML.
	 *
	 * What are the advantages?
	 *
	 * - Adheres to the Single Responsibility and Open/Close principles.
	 *
	 * How to use the pattern?
	 *
	 * 1) Define the interface to interact with users (Target class).
	 * 2) Create the adapter class that extends the interface and contains the service for the required functions.
	 * 3) The adapter composes the service to provide the necessary functionality.
	 */
	class TargetClass {
	public:
		virtual void show() {
			std::cout << "target class" << std::endl;
		}
	};
	class Service {
	public: 
		void serviceMethod() {
			std::cout << "service class" << std::endl;
		}
	};
	class ClassAdapter:public TargetClass, public Service {
	public:
		void show() {
			TargetClass::show();
			serviceMethod();
		}
	};

	class Objectadapter : public TargetClass {
	public:
		Objectadapter() {
			m_service = new Service();
		}
		~Objectadapter() {
			delete m_service;
		}
		void show() {
			TargetClass::show();
			m_service->serviceMethod();
		}
	private:
		Service* m_service;
	};
	/* Bridge Pattern
	 * When to use the pattern?
	 *
	 * Use the Bridge pattern in the following situation:
	 *
	 * - Example:
	 * Consider shapes (abstraction) and colors (implementation). 
	 * You have different shapes that can be filled with different colors.
	 *
	 * What are the advantages?
	 *
	 * - Avoids strong coupling between an abstraction and its implementation. This allows the abstraction and implementation to vary independently.
	 *
	 * How to use the pattern?
	 *
	 * 1) Define the interfaces for both the abstraction and the implementation.
	 * 2) The abstraction should be aggregated with the implementation.
	 */
	class Implementation {
	public:
		virtual void show() = 0;
	};
	class ConcreteImplementation1 : public Implementation {
	public:
		virtual void show() {
			std::cout << "ConcreteImplementation1" << std::endl;
		}
	};
	class ConcreteImplementation2 : public Implementation {
	public:
		virtual void show() {
			std::cout << "ConcreteImplementation2" << std::endl;
		}
	};
	class Abstraction {
	public:
		virtual void show() = 0;
		Abstraction(Implementation* i) {
			m_i = i;
		}
	protected:
		Implementation* m_i;
	};
	class RefinedAbstraction1 : public Abstraction{
	public:
		RefinedAbstraction1(Implementation* i):Abstraction(i) {
		}
		void show() {
			std::cout << "abstraction 1" << std::endl;
			m_i->show();
		}
	};
	class RefinedAbstraction2 : public Abstraction {
	public:
		RefinedAbstraction2(Implementation* i) :Abstraction(i) {
		}
		void show() {
			std::cout << "abstraction 2" << std::endl;
			m_i->show();
		}
	};
	/* Composite Pattern
	 * When to use the pattern?
	 *
	 * Use the Composite pattern in the following situation:
	 *
	 * - When representing part-whole hierarchies as tree structures.
	 *
	 * What are the advantages?
	 *
	 * - Utilizes polymorphism and recursion mechanisms for tree structures without requiring modifications.
	 *
	 * How to use the pattern?
	 *
	 * 1) Define the interface.
	 * 2) Create the leaf class that implements the interface.
	 * 3) Develop the composite class that implements the interface.
	 * 4) Define a container (holding references of composite and leaf objects) for the composite class.
	 * 5) Implement functions for adding and removing references within the composite class.
	 */
	class Component {
	public:
		virtual void show() = 0;
	};
	class Leaf: public Component {
	public:
		virtual void show() {
			std::cout << "Leaf " << this << std::endl;
		}
	};
	class Leaf2 : public Component {
	public:
		virtual void show() {
			std::cout << "Leaf2 " << this << std::endl;
		}
	};
	class Composite : public Component {
	public:
		virtual void show() {
			std::cout << "Size:" << m_children.size() << std::endl;
			for (auto it = m_children.begin(); it != m_children.end(); it++) {
				(*it)->show();
			}
		}
		void add(Component* c) {
			m_children.push_back(c);
		}
		void remove(Component* c) {
			auto it = std::find(m_children.begin(), m_children.end(), c);
			if(it != m_children.end())
				m_children.erase(it);
		}
		std::vector<Component*> getChildren() {
			return m_children;
		}
	private:
		std::vector<Component*> m_children;
	};
	/* Decorator Pattern
	 * When to use the pattern?
	 *
	 * Use the Decorator pattern in the following situations:
	 *
	 * - When you want to add additional functionality to an object at runtime.
	 * Examples:
	 * Creating a notifier that combines SMS, WeChat, and QQ.
	 * Adding multiple items of clothing to a person.
	 * Preparing coffee with honey and sugar.
	 *
	 * What are the advantages?
	 *
	 * - Provides more flexibility than inheritance; the number of subclasses required for inheritance could become unwieldy. With the Decorator pattern, you can simply add a decorator for the desired function.
	 *
	 * How to use the pattern?
	 *
	 * 1) Define the interface.
	 * 2) Implement an original class that adheres to the interface.
	 * 3) Create a decorator class that also implements the interface. This decorator contains a reference to the interface (aggregation) called a "wrappee". The decorator's constructor function takes the wrappee as a parameter.
	 * 4) Develop different decorators for different functions by extending the base decorator class. 
	 * These decorators should override and call the functions of the decorator they extend.
	 * Add extra work after the function.
	 */
	class Coffee {
	public:
		virtual void show() = 0;
	};
	class OriginalCoffee: public Coffee {
	public:
		virtual void show() {
			std::cout << "original coffee";
		}
	};
	class CoffeeDecorator : public Coffee {
	public:
		CoffeeDecorator(Coffee* c) {
			m_wrappee = c;
		}
		virtual void show() {
			m_wrappee->show();
		}
	private:
		Coffee* m_wrappee;
	};
	class HoneyDecorator : public CoffeeDecorator {
	public:
		HoneyDecorator(Coffee* c):CoffeeDecorator(c) {
		}
		/*override*/
		virtual void show() {
			CoffeeDecorator::show();
			std::cout << " add honey-";
		}
	};
	class MilkDecorator : public CoffeeDecorator {
	public:
		MilkDecorator(Coffee* c) :CoffeeDecorator(c) {
		}
		/*override*/
		virtual void show() {
			CoffeeDecorator::show();
			std::cout << " add milk-";
		}
	};
	/* Facade Pattern
	 * When to use the pattern?
	 *
	 * Use the Facade pattern in the following situations:
	 *
	 * - When you need to provide a simple interface to a complex subsystem.
	 * - The facade acts as an entry point to the subsystem, shielding users from its complexity.
	 * Examples:
	 * A video player requiring encode, decode, audio, and rendering subsystems.
	 *
	 * What are the advantages?
	 *
	 * - Simplifies the usage of a complex subsystem.
	 * - Encapsulates the subsystem, reducing its exposure to users and lowering coupling between users and the subsystem.
	 *
	 * How to use the pattern?
	 *
	 * 1) Define the facade class.
	 * 2) Define functions in the facade class that depend on other interfaces from the subsystem.
	 */
	class VideoFile {
	public:
		void showVideo() {
			std::cout << "show video" << std::endl;
		}
	};
	class AudioFile {
	public:
		void showAudio() {
			std::cout << "show audio" << std::endl;
		}
	};
	class VideoAudioMixer {
	public:
		void mixVideoAudio() {
			std::cout << "mix video and audio" << std::endl;
		}
	};
	class VideoFacade {
	public:
		void show() {
			VideoFile video;
			AudioFile audio;
			VideoAudioMixer mixer;
			video.showVideo();
			audio.showAudio();
			mixer.mixVideoAudio();
		}
	};
	/* Flyweight Pattern
	 * When to use the pattern?
	 *
	 * Use the Flyweight pattern in the following situations:
	 *
	 * - When dealing with a large number of objects that share intrinsic and extrinsic states.
	 * Example:
	 * 1) Rendering a large number of objects with rigid transformations.
	 *    - Meshes of the objects: intrinsic state
	 *    - Rigid transformations of objects: extrinsic state
	 * 2) A game with numerous repeating resources.
	 *
	 * What are the advantages?
	 *
	 * - Reduces memory usage by sharing common intrinsic states among objects.
	 *
	 * How to use the pattern?
	 *
	 * 1) Define a flyweight class for the intrinsic state.
	 * 2) Develop a flyweight factory to manage and store flyweight objects. The factory contains a container for references to flyweight objects.
	 * 3) When retrieving a flyweight object, return an existing object if it exists; otherwise, create a new flyweight object, save it in the factory, and then return it.
	 * 4) Create objects with both flyweight objects and extrinsic states.
	 */
	class AbstractCat {
	public:
		AbstractCat(const std::string&tex) {
			m_texture = tex;
		}
		std::string getTexture() {
			return  m_texture;
		}
		virtual void show() = 0;
	private:
		std::string m_texture;
	};
	class ConcreteCat: public AbstractCat {
	public:
		ConcreteCat(const std::string&tex):AbstractCat(tex){
		}
		void show() {
			std::cout << getTexture().c_str() << " " << this << " ";
		}
	};
	class CatFactory {
	public:
		~CatFactory() {
			for (auto i = 0; i < m_cats.size(); i++) {
				delete m_cats[i];
			}
		}
		AbstractCat* getCat(const std::string& t) {
			for (auto it = m_cats.begin(); it != m_cats.end(); it++) {
				if ((*it)->getTexture() == t) {
					return *it;
				}
			}
			m_cats.push_back(new ConcreteCat(t));
			return m_cats.back();
		}
	private:
		std::vector<AbstractCat*> m_cats;
	};
	class MovingCat {
	private:
		int m_pos;
		AbstractCat* m_cat;
	public:
		MovingCat(AbstractCat* c, int pos) {
			m_cat = c;
			m_pos = pos;
		}
		void show() {
			m_cat->show();
			std::cout << " position: " << m_pos << std::endl;
		}
	};
	/* Proxy Pattern
	 * When to use the pattern?
	 *
	 * Use the Proxy pattern in the following situations:
	 *
	 * - When you want to achieve lazy initialization, access control, caching request results, or local execution of remote services.
	 * Examples:
	 * 1) Third-party video (real service) and the cached video (proxy).
	 * 2) Cash (real service) and the credit card (proxy).
	 * 3) Database (real service) and the database proxy.
	 *
	 * What are the advantages?
	 *
	 * - The Proxy pattern provides a surrogate for the service with controlled accessibility.
	 *
	 * How to use the pattern?
	 *
	 * 1) Define an interface for both the proxy class and the real service class. They should have the same functions.
	 * 2) The proxy class holds a reference to the real service.
	 * 3) The functions in the proxy class call the corresponding functions in the real service.
	 * 4) Users interact with the proxy's functions using the defined interfaces.
	 */
	class Payment {
	public:
		virtual void show() = 0;
	};
	class Cash: public Payment {
	public:
		virtual void show() {
			std::cout << "here is the cash" << std::endl;
		}
	};
	class CreditCard : public Payment {
	public:
		CreditCard(Cash* c) {
			m_cash = c;
		}
		virtual void show() {
			m_cash->show();
		}
	private: 
		Cash* m_cash;
	};
}
