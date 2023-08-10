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
#include <stack>
 /*
 * The approaches are concerned with algorithms and the assignment of responsibilities between objects (10 types).
 */
namespace behavioral_pattern {
	/* Chain of Responsibility Pattern
	 * When to use the pattern?
	 *
	 * Use the Chain of Responsibility pattern in the following scenarios:
	 *
	 * - When there are different kinds of handlers, and their types and order are not predefined, or they are subject to change at runtime.
	 * - When multiple handlers need to process requests sequentially.
	 * Examples:
	 * TooltipText for GUIs; Order systems verifying users through multiple approaches.
	 *
	 * What are the advantages?
	 *
	 * - Provides control over the order of request processing.
	 * - Adheres to the Open/Close and Single Responsibility principles.
	 *
	 * How to use the pattern?
	 *
	 * 1) Define the Handler interface with functions:
	 *    a) set the next handler
	 *    b) handle the request of next handler
	 * 2) Implement the BaseHandler that follows the interface and provides a default handle function which passes the request to the next handler.
	 * 3) Define different Handlers that extend BaseHandler, implementing functions:
	 *    a) handle the request
	 *    b) check if they can handle the request
	 *    If a handler can handle the request, it calls the default handle function in the BaseHandler to pass the request to the next Handler.
	 * 4) Users need to form the chain of handlers using setNext(Handler*).
	 */

	class Handler {
	public:
		virtual void setNext(Handler* h) = 0;
		virtual void handle(int i) = 0;
	};
	class BaseHandler: public Handler {
	public:
		BaseHandler():m_next(nullptr) {}
		virtual void setNext(Handler* h) {
			m_next = h;
		}
		virtual void handle(int i) {
			if (nullptr != m_next) {
				m_next->handle(i);
			}
		}
	private:
		Handler* m_next;
	};
	class ConcreteHandler1: public BaseHandler {
	public:
		/*override*/
		virtual void handle(int i) {
			if (canHandle()) {
				std::cout << "handler1" << std::endl;
				BaseHandler::handle(i);
			}
		}
		bool canHandle() {
			return true;
		}
	};
	class ConcreteHandler2 : public BaseHandler {
	public:
		/*override*/
		virtual void handle(int i) {
			if (canHandle()) {
				std::cout << "handler2" << std::endl;
				BaseHandler::handle(i);
			}
		}
		bool canHandle() {
			return true;
		}
	};
	/* Command/Action/Transaction Pattern
	 * When to use the pattern?
	 *
	 * Use the Command pattern in the following situations:
	 *
	 * - When you want to encapsulate and operate on commands as objects.
	 * - When you need to queue, undo, or log commands.
	 *
	 * What are the advantages?
	 *
	 * - Adheres to the Open/Closed and Single Responsibility principles.
	 * - Supports undo operations, delayed execution, and command combination.
	 *
	 * How to use the pattern?
	 *
	 * 1) Define an interface Command with functions for execution.
	 * 2) Implement concrete command classes that implement the interface. These classes will be connected to receivers, and their execution functions will invoke actions on the receivers.
	 * 3) Define an Invoker class to collect and execute commands.
	 * 4) Users need to initialize concrete commands, receivers, and the invoker.
	 */

	class Command {
	public:
		virtual void execute() = 0;
	};
	class Receiver1 {
	public:
		void action() {
			std::cout << "action 1" << std::endl;
		}
	};
	class Receiver2 {
	public:
		void action() {
			std::cout << "action 2" << std::endl;
		}
	};
	class ConcreteCommand1: public Command {
	public:
		ConcreteCommand1(Receiver1*c) {
			m_receiver = c;
		}
		virtual void execute(){
			m_receiver->action();
		}
	private:
		Receiver1* m_receiver;
	};
	class ConcreteCommand2 : public Command {
	public:
		ConcreteCommand2(Receiver2*c) {
			m_receiver = c;
		}
		virtual void execute() {
			m_receiver->action();
		}
	private:
		Receiver2* m_receiver;
	};
	class Invoker {
	public:
		void executeCommands() {
			for (auto it = m_commands.begin(); it != m_commands.end(); it++) {
				(*it)->execute();
			}
		}
		void addCommand(Command* c) {
			m_commands.push_back(c);
		}
	private:
		std::vector<Command*> m_commands;
	};
	/* Iterator Pattern
	 * When to use the pattern?
	 *
	 * Use the Iterator pattern in the following scenarios:
	 *
	 * - When you want to provide a consistent interface to traverse complex data structures while hiding their underlying representations.
	 * - When you need to support different traversal methods of the same data.
	 * Example:
	 * C++ STL::iterator
	 *
	 * What are the advantages?
	 *
	 * - Adheres to the Single Responsibility and Open/Close principles.
	 * - Enables the use of multiple iterators in parallel.
	 *
	 * How to use the pattern?
	 *
	 * 1) Define the interfaces for the iterator and collection (aggregate).
	 *    - The iterator interface should contain pure virtual functions for accessing the next element and checking if there are more elements.
	 * 2) Define concrete iterator and concrete collection (aggregate) classes.
	 *    - The concrete iterator should hold a reference to the collection to access the dataset, and the concrete collection should implement the function to create a new iterator.
	 */
	class Iterator;	

	class IterableCollection {
	public:
		virtual Iterator* createIterator() = 0;
	};

	class ConcreteCollection : public IterableCollection {
	public:
		ConcreteCollection(const std::vector<int>& d):m_data(d){}
		virtual Iterator* createIterator();
		std::vector<int> m_data;
	};

	class Iterator {
	public:
		virtual int getNext() = 0;
		virtual bool hasMore() = 0;
	};

	class ConcreteIterator: public Iterator {
	public:
		ConcreteIterator(ConcreteCollection* c):
		m_collection(c), m_i(0){}
		virtual int getNext() {
			if (hasMore()) {
				return m_collection->m_data[m_i++];
			}
			else
				return 0;
		}
		virtual bool hasMore() {
			if (m_i < m_collection->m_data.size()) {
				return true;
			}
			else
				return false;
		}
	private:
		ConcreteCollection* m_collection;
		size_t m_i;
	};
	/* Mediator Pattern
	 * When to use the pattern?
	 *
	 * Use the Mediator pattern in the following situations:
	 *
	 * - When a group of objects need to communicate with each other, and a mediator can encapsulate how these objects interact, thus achieving loose coupling between them.
	 * Examples:
	 * Aircraft cockpit (mediator) for aircraft components.
	 *
	 * What are the advantages?
	 *
	 * - Adheres to the Single Responsibility principle.
	 * - Supports the Open/Close principle.
	 * - Reduces the coupling between components.
	 * - Enhances component reusability.
	 *
	 * How to use the pattern?
	 *
	 * 1) Define the interface for the mediator, including pure virtual functions for notifying components.
	 * 2) Define the interface for the components, with pure virtual functions for signals (sending) and slots (receiving).
	 * 3) The component interface should aggregate the mediator for notification.
	 * 4) Define the concrete mediator that implements the mediator interface. This concrete mediator aggregates the components for communication. The notify function handles communication between components.
	 * 5) Concrete components (e.g., Button) implement signals and slots. Signals call the mediator's notification function for communication.
	 */

	class Mediator;
	class Component {
	public:
		Component(Mediator* c) {
			m_mediator = c;
		}
		Mediator* getMediator() {
			return m_mediator;
		}
		virtual void send(const std::string&m) = 0;
		virtual void receive(const std::string&m) = 0;
	private:
		Mediator* m_mediator;
	};
	class Mediator {
	public: 
		virtual void notify(Component* c, const std::string&m) = 0;
	};
	class ConcreteMediator: public Mediator {
	public:
		void addComponents(Component* b, Component* t, Component* l) {
			m_button = b;
			m_textbox = t;
			m_label = l;
		}
		virtual void notify(Component* c, const std::string&m) {
			if (c == m_button) {
				m_textbox->receive(m);
			}else if (c == m_textbox) {
				m_button->receive(m);
			}else if (c == m_label) {
				m_label->receive(m);
			}
		}
	private:
		Component* m_button;
		Component* m_textbox;
		Component* m_label;
	};
	class Button : public Component {
	public:
		Button(Mediator* c):Component(c){}
		virtual void send(const std::string&m) {
			getMediator()->notify(this, m);
		}
		virtual void receive(const std::string&m) {
			std::cout << "button receives: " << m.c_str() 
				<< " sends" << std::endl;
		}
	};
	class Textbox : public Component {
	public:
		Textbox(Mediator* c) :Component(c) {}
		virtual void send(const std::string&m) {
			getMediator()->notify(this, m);
		}
		virtual void receive(const std::string&m) {
			std::cout << "texbox receives: " << m.c_str() 
				<< " sends" << std::endl;
		}
	};
	class Label : public Component {
	public:
		Label(Mediator* c) :Component(c) {}
		virtual void send(const std::string&m) {
			getMediator()->notify(this, m);
		}
		virtual void receive(const std::string&m) {
			std::cout << "label receives: " << m.c_str() 
				<< " sends" << std::endl;
		}
	};
	/* Memento Pattern
	 * When to use the pattern?
	 *
	 * Use the Memento pattern in the following situations:
	 *
	 * - When you need to create snapshots or archives for backup purposes.
	 * Examples:
	 * 1) Backing up game history. 2) Editors saving editing history.
	 *
	 * What are the advantages?
	 *
	 * - Allows creating snapshots without violating encapsulation.
	 *
	 * How to use the pattern?
	 *
	 * 1) Define three components: Originator, Memento, and Caretaker.
	 *    - Originator: The object that owns the state.
	 *    - Memento: Stores the data of the state.
	 *    - Caretaker: Manages the backup and restoration of the originator's state.
	 * 2) Originator should have functions to create a memento from its current state and to restore its state from a memento.
	 * 3) Caretaker should have a backup function to save a memento and a restore function to return the last backed-up memento.
	 */
	class GameMemento {
	public:
		GameMemento(const int&d) {
			m_data = d;
		}
		int getData() const {
			return m_data;
		}
	private:
		int m_data;
	};
	class GameOriginator {
	public:
		GameOriginator() : m_data(0) {}
		void play() {
			std::cout << "play : " << m_data++ << std::endl;
		}
		GameMemento save() {
			return GameMemento(m_data);
		}
		void restore(const GameMemento&m) {
			m_data = m.getData();
		}
	private:
		int m_data;
	};
	class GameCaretaker {
	public:
		void backup(const GameMemento&m) {
			m_history.push(m);
		}
		GameMemento undo() {
			GameMemento m = m_history.top();
			m_history.pop();
			return m;
		}
	private:
		std::stack<GameMemento> m_history;
	};
	/* Observer Pattern
	 * When to use the pattern?
	 *
	 * Use the Observer pattern in the following scenarios:
	 *
	 * - When a change in one object should trigger changes in multiple other objects (one-to-many dependency).
	 * - When you need to dynamically alter the set of notified objects (observers).
	 *
	 * Differences from the Command pattern:
	 * The Command pattern focuses on encapsulating commands and operations.
	 * The Observer pattern focuses on managing dependencies.
	 * Examples:
	 * Video and magazine subscriptions.
	 *
	 * What are the advantages?
	 *
	 * - Supports the Open/Close principle.
	 * - Establishes connections between objects at runtime.
	 *
	 * How to use the pattern?
	 *
	 * 1) Define an interface for subscribers with a function to update subscribers.
	 * 2) Concrete subscriber classes implement the subscriber interface.
	 * 3) Define the publisher class that aggregates the subscribers.
	 * 4) The publisher includes functions to add/delete subscribers and to notify subscribers of new information.
	 */

	class Subscriber {
	public:
		virtual void update(int i) = 0;
	};
	class ConcreteSubscriber1:public Subscriber {
	public:
		virtual void update(int i) {
			std::cout << "subscriber1 :" << i << std::endl;
		}
	};
	class ConcreteSubscriber2:public Subscriber {
	public:
		virtual void update(int i) {
			std::cout << "subscriber2 :" << i << std::endl;
		}
	};
	class Publisher {
	public:
		void notify(int i) {
			for (auto it = m_subscribers.begin(); it != m_subscribers.end(); it++) {
				(*it)->update(i);
			}
		}
		void subscribe(Subscriber*s) {
			m_subscribers.push_back(s);
		}
		void unsubscribe(Subscriber*s) {
			for (auto it = m_subscribers.begin(); it != m_subscribers.end(); it++) {
				if (*it == s) {
					m_subscribers.erase(it);
					return;
				}
			}
		}
	private:
		std::vector<Subscriber*> m_subscribers;
	};
	/* State Pattern
	 * When to use the pattern?
	 *
	 * Use the State pattern in the following scenarios:
	 *
	 * - When an object's behavior (context) depends on its internal state, and there are many possible states.
	 * - When the state of an object can be changed at runtime, either within the context or within the state itself.
	 * Examples:
	 * A document with states: draft, moderation, and published.
	 *
	 * What are the advantages?
	 *
	 * - Adheres to the Single Responsibility principle.
	 * - Supports the Open/Closed principle.
	 * - Reduces the need for switch or if-else statements in your code.
	 *
	 * How to use the pattern?
	 *
	 * 1) Define an interface for the state. This interface holds a reference to the context, allowing state switches.
	 * 2) Concrete state classes implement the interface and can transition to other states using the context's reference (note that states are aware of each other).
	 * 3) Define the context class, which maintains the current state and interacts with the state objects.
	 */
	class Player;
	class State {
	public:
		State(Player* p) {
			m_player = p;
		}
		Player* getPlayer() {
			return m_player;
		}
		virtual void play() = 0;
		virtual void lock() = 0;
		virtual void next() = 0;
	private:
		Player* m_player;
	};
	class Player {
	public:
		Player() :m_state(nullptr) {
			m_state = { nullptr };
		}
		void setState(State* s) {
			m_state = s;
		}
		void play() {
			m_state->play();
		}
		void lock() {
			m_state->lock();
		}
		void next() {
			m_state->next();
		}
		State* getState(int i) {
			return m_states[i];
		}
		void setState(int i, State*s) {
			m_states[i] = s;
		}
	private:
		State* m_state;
		State* m_states[3];
	};

	class PlayingState: public State{
	public:
		PlayingState(Player* p): State(p){}
		virtual void play() {
			std::cout << "playing..." << std::endl;
		}
		virtual void lock();
		virtual void next();
	};
	class LockState: public State{
	public:
		LockState(Player* p) : State(p) {}
		virtual void play();
		virtual void lock() {
			std::cout << "lock..." << std::endl;
		}
		virtual void next();
	};
	class ReadyState: public State{
	public:
		ReadyState(Player* p) : State(p) {}
		virtual void play();
		virtual void lock();
		virtual void next() {
			std::cout << "next..." << std::endl;
		}
	};
	/* Strategy (Policy) Pattern
	 * When to use the pattern?
	 *
	 * Use the Strategy pattern in the following situations:
	 *
	 * - When you want to use objects to represent different algorithms for a specific task (encapsulation), and you wish to change the algorithm being used within the context during runtime.
	 * Examples:
	 * Navigator (context), walking (strategy), bus (strategy)
	 *
	 * What are the advantages?
	 *
	 * - Enables changing algorithms (objects) at runtime.
	 * - Separates the algorithm's implementation from the logic of using the algorithm.
	 * - Adheres to the Aggregate/Composite principle.
	 * - Supports the Open/Closed principle.
	 *
	 * How to use the pattern?
	 * 1) Define an interface for the strategy.
	 * 2) Implement different strategies by creating classes that implement the interface.
	 * 3) Define the context class that aggregates the selected strategy.
	 * 4) Define the logic for using the strategy and provide a function to change the strategy dynamically.
	 */
	class Strategy {
	public:
		virtual void buildRoute(const std::string&a, const std::string&b) = 0;
	};
	class BikeStrategy: public Strategy {
	public:
		virtual void buildRoute(const std::string&a, const std::string&b) {
			std::cout << "bike: " << a.c_str() << "-" << b.c_str() << std::endl;
 		}
	};
	class WalkingStrategy : public Strategy {
	public:
		virtual void buildRoute(const std::string&a, const std::string&b) {
			std::cout << "walking: " << a.c_str() << "-" << b.c_str() << std::endl;
		}
	};
	class Navigator {
	public:
		Navigator() :m_strategy(nullptr) {}
		void showRoute(const std::string&a, const std::string&b) {
			m_strategy->buildRoute(a, b);
		}
		void setStrategy(Strategy* s) {
			m_strategy = s;
		}
	private:
		Strategy* m_strategy;
	};
	/* Template Method Pattern
	 * When to use the pattern?
	 *
	 * Use the Template Method pattern in the following scenarios:
	 *
	 * - When multiple algorithms share a significant portion of the same steps. You can place these common steps in the interface and delegate the varying parts to subclasses.
	 * - When you only need to modify specific steps within the algorithm, rather than the entire skeleton.
	 * Example:
	 * Creating a data miner for .Doc, .CSV, and .PDF files.
	 *
	 * What are the advantages?
	 *
	 * - Reduces code modification.
	 * - Enhances reusability.
	 *
	 * How to use the pattern?
	 * 1) Define the template method within the interface, outlining the steps of the algorithm.
	 * 2) Implement the shared steps in the parent class, and declare pure virtual functions for the customized steps.
	 * 3) Define concrete classes that implement the virtual steps to complete the algorithm.
	 */
	class AbstractClass {
	public:
		void templateMethod() {
			step1();
			step2();
			step3();
		}
		virtual void step1() = 0;
		virtual void step2() = 0;
		virtual void step3() {
			std::cout << "step3" << std::endl;
		}
	};
	class ConcreteClass1: public AbstractClass {
	public:

		virtual void step1() {
			std::cout << "ConcreteClass1 step1" << std::endl;
		}
		virtual void step2() {
			std::cout << "ConcreteClass1 step2" << std::endl;
		}
	};
	class ConcreteClass2: public AbstractClass {
	public:

		virtual void step1() {
			std::cout << "ConcreteClass2 step1" << std::endl;
		}
		virtual void step2() {
			std::cout << "ConcreteClass2 step2" << std::endl;
		}
		virtual void step3() {
			std::cout << "ConcreteClass2 step3" << std::endl;
		}
	};
	/* Visitor Pattern
	 * When to use the pattern?
	 *
	 * Use the Visitor pattern when you need to apply different operations to different objects within
	 * an object structure, and you want to avoid "polluting" their classes with these operations
	 * (adding complex code directly to the original code).
	 *
	 * What are the advantages?
	 *
	 * - Open/Closed principle.
	 * - Single Responsibility principle.
	 * - Visitors can gather information from elements.
	 *
	 * How to use the pattern?
	 *
	 * 1) Define the interface for accepting visitors, and let the objects explicitly choose which visitor to use.
	 * 2) Define the visitor interface, which includes functions to visit different elements.
	 * 3) Step 1 determines which visitor to use, and Step 2 determines which element to use it on.
	 */
	class Visitor;
	class ConcreteElement1;
	class ConcreteElement2;
	class Visitor {
	public:
		virtual void visit(ConcreteElement1* e) = 0;
		virtual void visit(ConcreteElement2* e) = 0;
	};
	class Element {
	public:
		virtual void accept(Visitor*v) = 0;
	};
	class ConcreteElement1: public Element {
	public:
		virtual void accept(Visitor*v) {
			v->visit(this);
		}
	};
	class ConcreteElement2: public Element {
	public:
		virtual void accept(Visitor*v) {
			v->visit(this);
		}
	};
	
	class ConcreteVisitor1: public Visitor {
	public:
		virtual void visit(ConcreteElement1* e) {
			std::cout << "ConcreteVisitor1 visit concrete element1" << std::endl;
		}
		virtual void visit(ConcreteElement2* e) {
			std::cout << "ConcreteVisitor1 visit concrete element2" << std::endl;
		}
	};
	class ConcreteVisitor2: public Visitor {
	public:
		virtual void visit(ConcreteElement1* e) {
			std::cout << "ConcreteVisitor2 visit concrete element1" << std::endl;
		}
		virtual void visit(ConcreteElement2* e) {
			std::cout << "ConcreteVisitor2 visit concrete element2" << std::endl;
		}
	};
}