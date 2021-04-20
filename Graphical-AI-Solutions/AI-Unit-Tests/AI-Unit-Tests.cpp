#include "pch.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "WorldState.hpp"
#include "WorldStateLocator.h"
#include "WorldObject.h"
#include "DerivedFromWorldObject.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PathfindingTest
{
	TEST_CLASS(WorldStateTest)
	{
	public:

		TEST_METHOD(AddingObjectWithUniqueIdGetsAdded)
		{
			auto id1 = WorldObjectIdentifier{ "obj1", 0 };	
			{
				auto obj1 = std::make_shared<WorldObject>(WorldObject());

				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(id1, obj1, true, true);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();
				
				auto count = worldState->getDrawables().size();
				Assert::AreEqual(count, static_cast<size_t>(1));

				count = worldState->getUpdatables().size();
				Assert::AreEqual(count, static_cast<size_t>(1));
			}
		}

		TEST_METHOD(AddingObjectsWithDuplicateIdThrowsException)
		{
			auto id1 = WorldObjectIdentifier{ "obj1", 0 };
			{
				auto obj1 = std::make_shared<WorldObject>(WorldObject());

				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(id1, obj1, true, true);

				// Add object with the same id again.
				auto func = [id1, obj1, worldState] {worldState->addNewObject(id1, obj1, true, true); };
				Assert::ExpectException<std::exception>(func);
			}
		}

		TEST_METHOD(AddingObjectToUpdatablesOnlyExistInUpdatables)
		{
			auto id1 = WorldObjectIdentifier{ "obj1", 0 };
			{
				auto obj1 = std::make_shared<WorldObject>(WorldObject());

				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(id1, obj1, false, true);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();

				auto count = worldState->getDrawables().size();
				Assert::AreEqual(count, static_cast<size_t>(0));

				count = worldState->getUpdatables().size();
				Assert::AreEqual(count, static_cast<size_t>(1));
			}
		}

		TEST_METHOD(AddingObjectToDrawablesOnlyExistInDrawables)
		{
			auto id1 = WorldObjectIdentifier{ "obj1", 0 };
			{
				auto obj1 = std::make_shared<WorldObject>(WorldObject());

				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(id1, obj1, true, false);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();

				auto count = worldState->getDrawables().size();
				Assert::AreEqual(count, static_cast<size_t>(1));

				count = worldState->getUpdatables().size();
				Assert::AreEqual(count, static_cast<size_t>(0));
			}
		}

		TEST_METHOD(removingWithCorrectIdRemovesItFromAllLists)
		{ 
			auto id1 = WorldObjectIdentifier{ "obj1", 0 };
			
			{
				auto obj1 = std::make_shared<WorldObject>(WorldObject());

				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(id1, obj1, true, true);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();

				// Make sure 1 object is in lists
				auto count = worldState->getDrawables().size();
				Assert::AreEqual(count, static_cast<size_t>(1));

				count = worldState->getUpdatables().size();
				Assert::AreEqual(count, static_cast<size_t>(1));
			
				// remove object
				worldState->removeObject(id1);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();

				auto count = worldState->getDrawables().size();
				Assert::AreEqual(count, static_cast<size_t>(0));

				count = worldState->getUpdatables().size();
				Assert::AreEqual(count, static_cast<size_t>(0));

				Assert::IsFalse(worldState->findObjectById(id1));
				Assert::IsFalse(worldState->findObjectIdByName(id1.name_));
			}
		}

		TEST_METHOD(removingWithWrongIdDoesNotChangeContainers)
		{
			auto id1 = WorldObjectIdentifier{ "obj1", 0 };
			{
				auto obj1 = std::make_shared<WorldObject>(WorldObject());

				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(id1, obj1, true, true);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();

				// Make sure 1 object is in lists
				auto count = worldState->getDrawables().size();
				Assert::AreEqual(count, static_cast<size_t>(1));

				count = worldState->getUpdatables().size();
				Assert::AreEqual(count, static_cast<size_t>(1));

				auto incorrectId = WorldObjectIdentifier{"incorrectId", 0};
				// Try remove object
				worldState->removeObject(incorrectId);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();

				auto count = worldState->getDrawables().size();
				Assert::AreEqual(count, static_cast<size_t>(1));

				count = worldState->getUpdatables().size();
				Assert::AreEqual(count, static_cast<size_t>(1));

				Assert::IsTrue(worldState->findObjectById(id1));
				Assert::IsTrue(worldState->findObjectIdByName(id1.name_));
			}
		}

		TEST_METHOD(gettingObjectShouldBeSameAsAddedObject)
		{
			WorldObject* obj1_ptr;
			auto id1 = WorldObjectIdentifier{ "obj1", 0 };
			{
				auto obj1 = std::make_shared<WorldObject>(WorldObject());
				obj1_ptr = obj1.get();

				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(id1, obj1, true, true);
			}

			WorldObject* obj2_ptr;
			auto id2 = WorldObjectIdentifier{ "obj2", 1 };
			{
				auto obj2 = std::make_shared<WorldObject>(WorldObject());
				obj2_ptr = obj2.get();

				auto worldState = WorldStateLocator::getWorldState();

				// Get obj1 from worldState and make sure its the same object as previously added
				auto newId1 = worldState->getObjectId(id1.name_);
				auto newObj1 = worldState->getObject(newId1);
				Assert::IsTrue(obj1_ptr == newObj1.get());
			
				// Add new obj2
				worldState->addNewObject(id2, obj2, true, true);
			}

			// Get WorldState, check obj1 and obj2, add obj1_duplicate
			{
				auto worldState = WorldStateLocator::getWorldState();

				// Get obj1 from worldState and make sure its the same object as previously added
				auto newId1 = worldState->getObjectId(id1.name_);
				auto newObj1 = worldState->getObject(newId1);
				Assert::IsTrue(obj1_ptr == newObj1.get());

				// Get obj2 from worldState and make sure its the same object as previously added
				auto newId2 = worldState->getObjectId(id2.name_);
				auto newObj2 = worldState->getObject(newId2);
				Assert::IsTrue(obj2_ptr == newObj2.get());
			}
		}

		TEST_METHOD(gettingDerivedObjectShouldBeSameAsAddedObject) {
			DerivedFromWorldObject* obj1_ptr;
			auto id1 = WorldObjectIdentifier{ "obj1", 0 };
			{
				auto obj1 = std::make_shared<DerivedFromWorldObject>(DerivedFromWorldObject(id1));
				obj1_ptr = obj1.get();

				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(id1, obj1, true, true);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();

				// Get obj1 from worldState and make sure its the same object as previously added
				auto newId1 = worldState->getObjectId(id1.name_);
				auto newObj1 = worldState->getObject(newId1);

				Assert::IsTrue(obj1_ptr == newObj1.get());

				auto derivedClassId = std::static_pointer_cast<DerivedFromWorldObject>(newObj1)->getId();
				Assert::AreEqual(id1.name_, derivedClassId.name_);
				Assert::AreEqual(id1.priority_, derivedClassId.priority_);
			}
		}

		TEST_METHOD(gettingDrawablesContainsAllDrawables)
		{
			auto id1 = new WorldObjectIdentifier{ "obj1", 0 };
			auto obj1 = std::make_shared<WorldObject>(*(new WorldObject()));

			auto id2 = new WorldObjectIdentifier{ "obj2", 0 };
			auto obj2 = std::make_shared<WorldObject>(*(new WorldObject()));

			auto id3 = new WorldObjectIdentifier{ "obj3", 0 };
			auto obj3 = std::make_shared<WorldObject>(*(new WorldObject()));

			{
				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(*id1, obj1, true, false);
				worldState->addNewObject(*id2, obj2, true, false);
				worldState->addNewObject(*id3, obj3, true, false);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();

				// check that each object is in drawableList 
				auto drawableList = worldState->getDrawables();

				auto count = drawableList.size();
				Assert::AreEqual(count, static_cast<size_t>(3));

				Assert::IsFalse(drawableList.find(*id1) == drawableList.end());
				Assert::IsFalse(drawableList.find(*id2) == drawableList.end());
				Assert::IsFalse(drawableList.find(*id3) == drawableList.end());
			}
		}

		TEST_METHOD(gettingUpdatablesContainsAllUpdatables)
		{
			auto id1 = new WorldObjectIdentifier{ "obj1", 0 };
			auto obj1 = std::make_shared<WorldObject>(*(new WorldObject()));

			auto id2 = new WorldObjectIdentifier{ "obj2", 0 };
			auto obj2 = std::make_shared<WorldObject>(*(new WorldObject()));

			auto id3 = new WorldObjectIdentifier{ "obj3", 0 };
			auto obj3 = std::make_shared<WorldObject>(*(new WorldObject()));

			{
				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(*id1, obj1, false, true);
				worldState->addNewObject(*id2, obj2, false, true);
				worldState->addNewObject(*id3, obj3, false, true);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();

				// check that each object is in updatableList 
				auto updatableList = worldState->getUpdatables();

				auto count = updatableList.size();
				Assert::AreEqual(count, static_cast<size_t>(3));

				Assert::IsFalse(updatableList.find(*id1) == updatableList.end());
				Assert::IsFalse(updatableList.find(*id2) == updatableList.end());
				Assert::IsFalse(updatableList.find(*id3) == updatableList.end());
			}
		}

		TEST_METHOD(findObjectWithCorrectIdReturnsTrue)
		{
			auto id1 = new WorldObjectIdentifier{ "obj1", 0 };
			auto obj1 = std::make_shared<WorldObject>(*(new WorldObject()));
			{
				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(*id1, obj1, true, true);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();

				Assert::IsTrue(worldState->findObjectById(*id1));
			}
		}

		TEST_METHOD(findObjectWithIncorrectIdReturnsFalse)
		{
			auto id1 = new WorldObjectIdentifier{ "obj1", 0 };
			auto obj1 = std::make_shared<WorldObject>(*(new WorldObject()));
			{
				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(*id1, obj1, true, true);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();

				auto incorrectId = new WorldObjectIdentifier{ "incorrectId", 0 };

				Assert::IsFalse(worldState->findObjectById(*incorrectId));
			}
		}

		TEST_METHOD(findObjectIdWithCorrectNameReturnsTrue)
		{
			auto id1 = new WorldObjectIdentifier{ "obj1", 0 };
			auto obj1 = std::make_shared<WorldObject>(*(new WorldObject()));
			{
				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(*id1, obj1, true, true);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();

				Assert::IsTrue(worldState->findObjectIdByName(id1->name_));
			}
		}

		TEST_METHOD(findObjectIdWithIncorrectNameReturnsFalse)
		{
			auto id1 = new WorldObjectIdentifier{ "obj1", 0 };
			auto obj1 = std::make_shared<WorldObject>(*(new WorldObject()));
			{
				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(*id1, obj1, true, true);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();

				auto incorrectId = WorldObjectIdentifier{ "incorrectId", 0 };

				Assert::IsFalse(worldState->findObjectIdByName(incorrectId.name_));
			}
		}

		TEST_METHOD(gettingObjectWithIncorrectIdThrowsException)
		{
			auto id1 = new WorldObjectIdentifier{ "obj1", 0 };
			auto obj1 = std::make_shared<WorldObject>(*(new WorldObject()));
			{
				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(*id1, obj1, true, true);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();

				auto incorrectId = WorldObjectIdentifier{ "incorrectId", 0 };

				// getting object that does not exist
				auto func = [incorrectId, worldState] {worldState->getObject(incorrectId); };
				Assert::ExpectException<std::exception>(func);
			}
		}

		TEST_METHOD(gettingObjectIdWithIncorrectNameThrowsException)
		{
			auto id1 = new WorldObjectIdentifier{ "obj1", 0 };
			auto obj1 = std::make_shared<WorldObject>(*(new WorldObject()));
			{
				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(*id1, obj1, true, true);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();

				auto incorrectId = WorldObjectIdentifier{ "incorrectId", 0 };

				// getting object that does not exist
				auto func = [incorrectId, worldState] {worldState->getObjectId(incorrectId.name_); };
				Assert::ExpectException<std::exception>(func);
			}
		}

		TEST_METHOD(iteratingThroughDrawableObjectsIsInPriorityOrder) 
		{
			auto id1 = new WorldObjectIdentifier{ "obj1", 1 };
			auto obj1 = std::make_shared<WorldObject>(*(new WorldObject()));

			auto id2 = new WorldObjectIdentifier{ "obj2", 2 };
			auto obj2 = std::make_shared<WorldObject>(*(new WorldObject()));

			auto id3 = new WorldObjectIdentifier{ "obj3", 3 };
			auto obj3 = std::make_shared<WorldObject>(*(new WorldObject()));

			{
				// Initialize global WorldStateLocator Service
				WorldStateProvider* worldState = new WorldStateProvider();
				WorldStateLocator::provide(worldState);

				// Add new obj1
				worldState->addNewObject(*id2, obj2, true, false);
				worldState->addNewObject(*id3, obj3, true, false);
				worldState->addNewObject(*id1, obj1, true, false);
			}

			{
				auto worldState = WorldStateLocator::getWorldState();

				// check that each object is in drawableList 
				auto drawableList = worldState->getDrawables();

				auto count = drawableList.size();
				Assert::AreEqual(count, static_cast<size_t>(3));

				Assert::IsFalse(drawableList.find(*id1) == drawableList.end());
				Assert::IsFalse(drawableList.find(*id2) == drawableList.end());
				Assert::IsFalse(drawableList.find(*id3) == drawableList.end());

				auto drawableIterator = drawableList.begin();
				Assert::IsTrue(drawableIterator->first.name_ == id1->name_);
				++drawableIterator;
				Assert::IsTrue(drawableIterator->first.name_ == id2->name_);
				++drawableIterator;
				Assert::IsTrue(drawableIterator->first.name_ == id3->name_);
			}
		}

		TEST_METHOD(releasingWorldStateDoesNotYieldMemoryLeaks)
		{
			CrtCheckMemory check;
			{ 
				auto id1 = WorldObjectIdentifier{ "obj1", 0 };
				auto id2 = WorldObjectIdentifier{ "obj2", 0 };
				auto id3 = WorldObjectIdentifier{ "obj3", 0 };
				auto id4 = WorldObjectIdentifier{ "obj4", 0 };

				{
					auto obj1 = std::make_shared<WorldObject>(WorldObject());
					auto obj2 = std::make_shared<WorldObject>(WorldObject());
					auto obj3 = std::make_shared<WorldObject>(WorldObject());
					auto obj4 = std::make_shared<WorldObject>(WorldObject());

					// Initialize global WorldStateLocator Service
					WorldStateProvider* worldState = new WorldStateProvider();
					WorldStateLocator::provide(worldState);

					// Add all objects
					worldState->addNewObject(id1, obj1, true, true);
					worldState->addNewObject(id2, obj2, false, true);
					worldState->addNewObject(id3, obj3, true, false);
					worldState->addNewObject(id4, obj4, true, true);
				}

				{
					auto worldState = WorldStateLocator::getWorldState();

					// remove all objects
					worldState->removeObject(id1);
					worldState->removeObject(id2);
					worldState->removeObject(id3);

					delete worldState;
				}
			}
		}
	};
}