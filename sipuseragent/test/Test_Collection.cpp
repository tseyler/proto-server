
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* Test_Collection.cpp                                              			*
* Copyright (c) 2012, by Control4 Inc.  All rights reserved.	            *
* Created on: Jan 11, 2012													*
* Author: Terry Seyler														*
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#include <test/UnitTest.hpp>
#include "TestReporter.h"
#include "ReportAssert.h"

#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "userAgentHelper.h"

using namespace C4UserAgent;

SUITE(Test_Collection)
{
	typedef std::vector<int>					testIntCollection;
	typedef	testIntCollection::iterator			testIntIterator;

    struct CollectionFixture
    {
    	CollectionFixture()
        {
    		addToCollection<testIntCollection, int>(intColl_, 1000);
    		addToCollection<testIntCollection, int>(intColl_, 65);
    		addToCollection<testIntCollection, int>(intColl_, 14);


        }

        ~CollectionFixture()
        {

        }

        testIntCollection 	intColl_;

    };

    TEST_FIXTURE(CollectionFixture, AddIntToCollectionTest)
    {
    	size_t expected = 4;
    	addToCollection<testIntCollection, int>(intColl_, 60);
    	CHECK_EQUAL( expected, intColl_.size() );
    }

    TEST_FIXTURE(CollectionFixture, RemoveIntFromCollectionTest)
    {
    	size_t expected = 2;
    	removeFromCollection<testIntCollection, testIntIterator, int>(intColl_, 65);	// this one exists
    	removeFromCollection<testIntCollection, testIntIterator, int>(intColl_, 99);	// this one does not
    	CHECK_EQUAL( expected, intColl_.size() );
    }

    TEST_FIXTURE(CollectionFixture, EmptyIntCollectionTest)
    {
    	size_t expected = 0;
    	emptyCollection<testIntCollection>(intColl_);
    	CHECK_EQUAL( expected, intColl_.size() );
    }

    TEST_FIXTURE(CollectionFixture, CatIntCollectionTest)
    {
    	testIntCollection srcColl;
    	addToCollection<testIntCollection, int>(srcColl, 55);
    	addToCollection<testIntCollection, int>(srcColl, 45);

    	size_t expected = 5;
    	catCollection<testIntCollection, testIntIterator, int>(srcColl, intColl_);
    	CHECK_EQUAL( expected, intColl_.size() );
    }

    TEST_FIXTURE(CollectionFixture, CopyIntCollectionTest)
    {
    	testIntCollection srcColl;

    	size_t expected = 3;
    	copyCollection<testIntCollection>(intColl_, srcColl);
    	CHECK_EQUAL( expected, srcColl.size() );
    }

    TEST_FIXTURE(CollectionFixture, getFromIntCollectionTest)
    {
    	int expected = intColl_.front();
    	int actual = getFromCollection<testIntCollection, int>(intColl_, 0, 0);
    	CHECK_EQUAL( expected, actual);

    	expected = 0;
    	actual = getFromCollection<testIntCollection, int>(intColl_, 6, 0);	// out of bounds
    	CHECK_EQUAL( expected, actual);
    }

    TEST_FIXTURE(CollectionFixture, getIteratorFromIntCollectionTest)
    {
    	testIntIterator actual = getIteratorFromCollection<testIntCollection, testIntIterator, int>(intColl_, 14);
    	CHECK( actual != intColl_.end());

    	actual = getIteratorFromCollection<testIntCollection, testIntIterator, int>(intColl_, 2222);
    	CHECK( actual == intColl_.end() );
    }

    TEST_FIXTURE(CollectionFixture, getFrontFromIntCollectionTest)
    {
    	int expected = intColl_.front();
    	int actual = getFrontFromCollection<testIntCollection, int>(intColl_, 0);
    	CHECK_EQUAL( expected, actual );

    	testIntCollection srcColl;
    	expected = 0;
    	actual = getFrontFromCollection<testIntCollection, int>(srcColl, 0);
    	CHECK_EQUAL( expected, actual );
    }

    TEST_FIXTURE(CollectionFixture, getBackFromIntCollectionTest)
    {
    	int expected = intColl_.back();
    	int actual = getBackFromCollection<testIntCollection, int>(intColl_, 0);
    	CHECK_EQUAL( expected, actual );

    	testIntCollection srcColl;
    	expected = 0;
    	actual = getBackFromCollection<testIntCollection, int>(srcColl, 0);
    	CHECK_EQUAL( expected, actual );
    }

    TEST_FIXTURE(CollectionFixture, getNextFromIntCollectionTest)
    {
    	int expected = 65;
    	int actual = getNextFromCollection<testIntCollection, testIntIterator, int>(intColl_, intColl_.front());
    	CHECK_EQUAL( expected, actual );

    	expected = 14;
    	actual = getNextFromCollection<testIntCollection, testIntIterator, int>(intColl_, intColl_.back());
    	CHECK_EQUAL( expected, actual );
    }


}
