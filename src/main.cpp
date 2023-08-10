/*
 * C++ Design Patterns
 * Author: Jinta Zheng [https://github.com/jintazheng]
 *
 * Source code is licensed under MIT License
 * (for more details see LICENSE)
 *
 */

#include "creational_pattern.cpp"
#include "structural_pattern.cpp"
#include "behavioral_pattern.cpp"
using namespace creational_pattern;
using namespace structural_pattern;
using namespace behavioral_pattern;
/*creational patterns*/
void simple_factory() {
	SimpleFactory factory;
	auto product = factory.creatProduct(ProductType::PRODUCTA);
	product->show();
}
void factory_method() {
	AbstractFactory* factory_ptr = new FactoryA();
	auto product = factory_ptr->createProduct();
	product->show();
}
void abstract_factory() {
	AbstractFactory2* factory_ptr = new FactoryB2();
	auto product = factory_ptr->createProduct();
	product->show();
	auto product2 = factory_ptr->createProduct2();
	product2->show();
}
void builder() {
	Builder* builder_ptr = new ConcreteBuilderA();
	Director director;
	director.setBuilder(builder_ptr);
	director.createProduct2();
	auto product = director.getProduct();
	product.show();
}
void prototype() {
	ConcretePrototype* prototype_ptr = new ConcretePrototype();
	prototype_ptr->setData("hello");
	prototype_ptr->setData2("world");
	prototype_ptr->show();
	prototype_ptr->clone()->show();
}
Singleton::Ptr Singleton::m_instance = nullptr;
std::mutex Singleton::m_mutex;

void singleton() {
	Singleton::Ptr singleton = Singleton::getInstance();
	singleton->show();
	singleton = Singleton::getInstance();
	singleton->show();
}

/*structural patterns*/
void adapter() {
	TargetClass* classAdapter = new ClassAdapter();
	classAdapter->show();
	TargetClass* objectAdapter = new Objectadapter();
	objectAdapter->show();
}
void bridge() {
	Abstraction *r0 = new RefinedAbstraction1(new ConcreteImplementation1());
	r0->show();
	Abstraction *r1 = new RefinedAbstraction2(new ConcreteImplementation2());
	r1->show();
}
void composite() {
	Composite *tree = new Composite();
	tree->add(new Leaf());
	tree->add(new Leaf());
	tree->add(new Leaf2());
	Composite *tree2 = new Composite();
	tree->add(tree2);
	tree2->add(new Leaf());
	tree2->add(new Leaf2());
	tree->show();
}
void decorator() {
	Coffee *coffee = new OriginalCoffee();
	coffee->show();
	std::cout << std::endl;
	coffee = new HoneyDecorator(coffee);
	coffee->show();
	std::cout << std::endl;
	coffee = new MilkDecorator(coffee);
	coffee->show();
	std::cout << std::endl;
}
void facade() {
	VideoFacade *facade = new VideoFacade();
	facade->show();
}
void flyweight() {
	CatFactory catFactory;
	MovingCat c0(catFactory.getCat("black"), 0);
	c0.show();
	MovingCat c1(catFactory.getCat("black"), 1);
	c1.show();
	MovingCat c2(catFactory.getCat("white"), 2);
	c2.show();
}
void proxy() {
	Cash money;
	Payment* pay = new CreditCard(&money);
	pay->show();
}
/*behavioral patterns*/
void chain_of_responsibility() {
	Handler* h0 = new BaseHandler();
	Handler* h1 = new ConcreteHandler1();
	Handler* h2 = new ConcreteHandler2();
	h0->setNext(h1);
	h1->setNext(h2);
	h0->handle(0);
}
void command() {
	Command* c1 = new ConcreteCommand1(new Receiver1());
	Command* c2 = new ConcreteCommand2(new Receiver2());
	Invoker invoker;
	invoker.addCommand(c1);
	invoker.addCommand(c2);
	invoker.executeCommands();
}
Iterator* ConcreteCollection::createIterator() {
	return (new ConcreteIterator(this));
}
void iterator() {
	std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7 };
	ConcreteCollection *collection = new ConcreteCollection(data);
	Iterator *iter = collection->createIterator();
	while (iter->hasMore()) {
		std::cout << iter->getNext() << std::endl;
	}
}
void mediator() {
	ConcreteMediator *mediator = new ConcreteMediator();
	behavioral_pattern::Component* button = new Button(mediator);
	behavioral_pattern::Component* textbox = new Textbox(mediator);
	behavioral_pattern::Component* label = new Label(mediator);
	mediator->addComponents(button, textbox, label);
	button->send("button");
	textbox->send("textbox");
	label->send("label");
}
void memento() {	
	GameCaretaker history;
	GameOriginator game;
	history.backup(game.save());
	game.play();
	game.play();
	game.play();
	game.restore(history.undo());
	game.play();
}
void observer() {
	Subscriber* s0 = new ConcreteSubscriber1();
	Subscriber* s1 = new ConcreteSubscriber2();
	Publisher publisher;
	publisher.subscribe(s0);
	//publisher.subscribe(s1);
	publisher.notify(0);
	publisher.notify(1);
}

void PlayingState::lock() {
	if (getPlayer()->getState(1) == nullptr) {
		getPlayer()->setState(1, new LockState(getPlayer()));
	}
	getPlayer()->setState(getPlayer()->getState(1));
	getPlayer()->lock();
}
void PlayingState::next() {
	if (getPlayer()->getState(2) == nullptr) {
		getPlayer()->setState(2, new ReadyState(getPlayer()));
	}
	getPlayer()->setState(getPlayer()->getState(2));
	getPlayer()->next();
}
void LockState::play() {
	if (getPlayer()->getState(0) == nullptr) {
		getPlayer()->setState(0, new PlayingState(getPlayer()));
	}
	getPlayer()->setState(getPlayer()->getState(0));
	getPlayer()->play();
}
void LockState::next() {
	if (getPlayer()->getState(2) == nullptr) {
		getPlayer()->setState(2, new ReadyState(getPlayer()));
	}
	getPlayer()->setState(getPlayer()->getState(2));
	getPlayer()->next();
}
void ReadyState::play() {
	if (getPlayer()->getState(0) == nullptr) {
		getPlayer()->setState(0, new PlayingState(getPlayer()));
	}
	getPlayer()->setState(getPlayer()->getState(0));
	getPlayer()->play();
}
void ReadyState::lock() {
	if (getPlayer()->getState(1) == nullptr) {
		getPlayer()->setState(1, new LockState(getPlayer()));
	}
	getPlayer()->setState(getPlayer()->getState(1));
	getPlayer()->lock();
}

void state() {
	Player* player = new Player();
	State* state = new LockState(player);
	player->setState(1, state);
	player->setState(state);
	player->lock();
	player->play();
	player->next();
	player->play();
}
void strategy() {
	Strategy* bike = new BikeStrategy();
	Strategy* walk = new WalkingStrategy();
	Navigator navigator;
	navigator.setStrategy(bike);
	navigator.showRoute("a", "b");
	navigator.setStrategy(walk);
	navigator.showRoute("b", "c");
}
void template_method() {
	AbstractClass* template_p1 = new ConcreteClass1();
	AbstractClass* template_p2 = new ConcreteClass2();
	template_p1->templateMethod();
	template_p2->templateMethod();
}
void visitor() {
	Visitor* v1 = new ConcreteVisitor1();
	Visitor* v2 = new ConcreteVisitor2();
	ConcreteElement1* e1 = new ConcreteElement1();
	ConcreteElement2* e2 = new ConcreteElement2();
	e1->accept(v1);
	e1->accept(v2);
	e2->accept(v1);
	e2->accept(v2);
}
int main() {
	std::cout << "please choose a pattern" << std::endl;
	system("pause");
	return 0;
}