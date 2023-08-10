/*
 * C++ Design Patterns
 * Author: Jinta Zheng [https://github.com/jintazheng]
 *
 * Source code is licensed under MIT License
 * (for more details see LICENSE)
 *
 */

#include <iostream>
#include <mutex>
 /*
 * The approaches are concerned with various object creation mechanisms (for flexibility and reusability) (6 types).
 */
namespace creational_pattern {
	/* Simple Factory Pattern
	 * When to use the pattern?
	 *
	 * Use the Simple Factory pattern in the following situations:
	 *
	 * - When a product comes in multiple variants, such as ProductA and ProductB.
	 * - Utilize a factory class to create objects (ProductA or ProductB) based on specified flags.
	 * - Implement an interface for the product, supporting the Dependency Inversion Principle and promoting reusability.
	 * - Provide a function to create objects without exposing the object's implementation details.
	 *
	 * What are the advantages?
	 *
	 * - Users are shielded from the intricacies of different product variants.
	 *
	 * What are the disadvantages?
	 *
	 * - If a new variant, like ProductC, is introduced:
	 *   1) The factory class needs to be modified.
	 */
	class Product {
	public:
		virtual void show() = 0;
	};
	class ProductA : public Product {
	public:
		virtual void show() {
			std::cout << "productA" << std::endl;
		}
	};
	class ProductB : public Product {
	public:
		virtual void show() {
			std::cout << "productB" << std::endl;
		}
	};
	enum ProductType {
		PRODUCTA,
		PRODUCTB
	};
	class SimpleFactory {
	public:
		Product* creatProduct(ProductType type) {
			switch (type) {
			case ProductType::PRODUCTA:
				return new ProductA();
				break;
			case ProductType::PRODUCTB:
				return new ProductB();
				break;
			}
		}
	};
	/* Factory Pattern
	 * When to use the pattern?
	 *
	 * Similar to the Simple Factory pattern, but with a solution to its disadvantages.
	 * This pattern delays the instantiation of products to the factory's subclasses.
	 *
	 * What are the advantages?
	 *
	 * - Prevents the need to modify the factory class when new products are introduced.
	 *
	 * How to use the pattern?
	 *
	 * 1) Define an interface for the factory class, and use different subclasses to create various products.
	 * 2) With this approach, you only need to add a new subclass for each new product, rather than modifying the factory class (following the Open/Closed Principle).
	 */
	class AbstractFactory {
	public:
		virtual Product* createProduct() = 0;
	};
	class FactoryA: public AbstractFactory{
	public:
		virtual Product* createProduct() {
			return new ProductA();
		}
	};
	class FactoryB : public AbstractFactory {
	public:
		virtual Product* createProduct() {
			return new ProductB();
		}
	};
	/* Abstract Factory Pattern
	 * When to use the pattern?
	 *
	 * Use the Abstract Factory pattern when there are multiple families of related classes.
	 * For example, consider:
	 * Family A: ProductA and ProductB
	 * Family B: Product2A and Product2B
	 * A is one family, and B is another family.
	 * Another example could be creating a UI across different platforms:
	 * Platform A: Window
	 * Platform B: Mac
	 * Within each platform, there are products like buttons (Product) and checkboxes (Product2).
	 *
	 * What are the advantages?
	 *
	 * - Extends the Factory Method pattern to handle situations with multiple families of classes.
	 *
	 * How to use the pattern?
	 *
	 * Build upon the Factory Method pattern by adding additional virtual functions to handle multiple families.
	 */

	class Product2 {
	public:
		virtual void show() = 0;
	};
	class Product2A : public Product2 {
	public:
		virtual void show() {
			std::cout << "product2A" << std::endl;
		}
	};
	class Product2B : public Product2 {
	public:
		virtual void show() {
			std::cout << "product2B" << std::endl;
		}
	};

	class AbstractFactory2 {
	public:
		virtual Product* createProduct() = 0;
		virtual Product2* createProduct2() = 0;
	};
	class FactoryA2 : public AbstractFactory2 {
	public:
		virtual Product* createProduct() {
			return new ProductA();
		}
		virtual Product2* createProduct2() {
			return new Product2A();
		}
	};
	class FactoryB2 : public AbstractFactory2 {
	public:
		virtual Product* createProduct() {
			return new ProductB();
		}
		virtual Product2* createProduct2() {
			return new Product2B();
		}
	};
	/* Builder Pattern
	 * When to use the pattern?
	 *
	 * Use the Builder pattern in the following situations:
	 *
	 * - When dealing with complex classes that are composed of multiple parts.
	 * - For instance, a house comprises windows, doors, and a ceiling.
	 * - The Builder is responsible for implementing the elements (like a wooden door or a steel door).
	 * - Different builders can have different implementations.
	 * - The Director orchestrates the order of construction.
	 * - For example:
	 *   - We can construct a house using the composition of windows, doors, and a ceiling.
	 *   - We can also construct a house using the composition of windows and a ceiling.
	 * - This pattern is useful when users need to provide more information for constructing objects, and the implementation/composition is independent of parts.
	 *
	 * What are the advantages?
	 *
	 * - Avoids the "telescopic constructor" problem.
	 *   - For example, instead of:
	 *     ```
	 *     class Product3 {
	 *         Product3(string a) { ... }
	 *         Product3(string a, string b) { ... }
	 *         Product3(string a, string b, string c) { ... }
	 *         ...
	 *     }
	 *     ```
	 * - Can use generators to construct composite trees or other complex objects.
	 *
	 * How to use the pattern?
	 *
	 * 1) The Product contains multiple parts.
	 * 2) Use the Builder to implement each part.
	 * 3) First, define the interface of the Builder, and then define the concrete Builders.
	 * 4) The Director handles the composition of the implementation.
	 */

	class Product3 {
	public:
		void setPartA(const std::string&p) {
			m_partA = p;
		}
		void setPartB(const std::string&p) {
			m_partB = p;
		}
		void setPartC(const std::string&p) {
			m_partC = p;
		}
		void show() {
			std::cout << 
				m_partA.c_str() << ", " << 
				m_partB.c_str() << ", " <<
				m_partC.c_str() << std::endl;
		}
	private:
		std::string m_partA;
		std::string m_partB;
		std::string m_partC;
	};
	class Builder {
	public:
		virtual void buildPartA(const std::string&p) = 0;
		virtual void buildPartB(const std::string&p) = 0;
		virtual void buildPartC(const std::string&p) = 0;
		virtual Product3 getProduct() = 0;
	protected:
		Product3 m_product;
	};
	class ConcreteBuilderA : public Builder {
	public:
		virtual void buildPartA(const std::string&p) {
			m_product.setPartA("A" + p);
		}
		virtual void buildPartB(const std::string&p) {
			m_product.setPartB("A" + p);
		}
		virtual void buildPartC(const std::string&p) {
			m_product.setPartC("A" + p);
		}
		virtual Product3 getProduct() {
			return m_product;
		}
	};
	class ConcreteBuilderB : public Builder {
	public:
		virtual void buildPartA(const std::string&p) {
			m_product.setPartA("B" + p);
		}
		virtual void buildPartB(const std::string&p) {
			m_product.setPartB("B" + p);
		}
		virtual void buildPartC(const std::string&p) {
			m_product.setPartC("B" + p);
		}
		virtual Product3 getProduct() {
			return m_product;
		}
	};
	class Director {
	public:
		Director() :m_builder(nullptr) {}
		void setBuilder(Builder* b) {
			m_builder = b;
		}
		void createProduct() {
			if (m_builder == nullptr) {
				std::cout << "without builder" << std::endl;
				return;
			}
			m_builder->buildPartA("0");
			m_builder->buildPartB("1");
			m_builder->buildPartC("2");
		}
		void createProduct2() {
			if (m_builder == nullptr) {
				std::cout << "without builder" << std::endl;
				return;
			}
			m_builder->buildPartA("great");
			m_builder->buildPartB("great");
			m_builder->buildPartC("great");
		}
		Product3 getProduct() {
			if (m_builder == nullptr) {
				std::cout << "without builder" << std::endl;
				return Product3();
			}
			return m_builder->getProduct();
		}
	protected:
		Builder *m_builder;
	};
	/* Prototype Pattern
	 * When to use the pattern?
	 *
	 * Use the Prototype pattern when you need to clone an object without knowing the details of its class.
	 *
	 * What are the advantages?
	 *
	 * - Allows object cloning without being tightly coupled to the class.
	 *
	 * How to use the pattern?
	 *
	 * 1) Create an interface for the `clone()` method. If the class already exists, simply add the `clone()` method.
	 * 2) Define the constructor function with an object of the class as a parameter, and copy all variables into the constructor function.
	 * 3) Invoke the constructor function of the parent class for the subclass.
	 * 4) Each class must explicitly override the `clone` method.
	 */
	class Prototype {
	public:
		virtual Prototype* clone() = 0;
		Prototype() {}
		Prototype(Prototype *p) {
			this->m_data = p->getData();
		}
		std::string getData() { return m_data; }
		void setData(const std::string&d) { m_data = d; }
		virtual void show() = 0;
	private:
		std::string m_data;
	};
	class ConcretePrototype: public Prototype {
	public:
		virtual Prototype* clone() {
			return new ConcretePrototype(this);
		}
		ConcretePrototype() {}
		ConcretePrototype(ConcretePrototype *p):Prototype(p) {
			this->m_data2 = p->getData2();
		}
		std::string getData2() { return m_data2; }
		void setData2(const std::string&d) { m_data2 = d; }
		virtual void show() {
			std::cout << this->getData().c_str() << ", " << this->getData2().c_str() << std::endl;
		}
	private:
		std::string m_data2;
	};
	/* Singleton Pattern
	 * When to use the pattern?
	 *
	 * Use the Singleton pattern when you require exactly one global instance of a class.
	 *
	 * What are the advantages?
	 *
	 * - Ensures only one class and one instance.
	 *
	 * How to use the pattern?
	 *
	 * 1) Create a private static variable for the object.
	 * 2) Implement a public static function to access the object.
	 * 3) Create a private constructor function.
	 * 4) The static function will create a new object upon its first call; subsequent calls will return the static variable.
	 * 5) Prohibit copying and assignment to enforce the Singleton behavior.
	 * 6) Utilize `shared_ptr` to automatically release dynamically allocated memory.
	 * 7) To prevent errors due to multiple threads simultaneously calling the `getInstance` function, add a mutex lock to ensure that only one instance is created.
	 */
	class Singleton {
	public:
		typedef std::shared_ptr<Singleton> Ptr;

		Singleton(Singleton const&) = delete;
		Singleton& operator=(Singleton const&) = delete;
		static Ptr getInstance() {
			std::lock_guard<std::mutex> lk(m_mutex);
			if (nullptr == m_instance) {
				m_instance = Ptr(new Singleton());
			}
			return m_instance;
		}
		void show() {
			std::cout << "I am singleton !" << std::endl;
		}
	private:
		static Ptr m_instance;
		static std::mutex m_mutex;
		Singleton() {}
	};

}
