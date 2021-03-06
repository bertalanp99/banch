#include "gtest/gtest.h"
#include "string.hxx" // TODO set correct path and add using directive

TEST(StringTest, Create)
{
	// create empty String
	String foo;
	EXPECT_EQ(0, foo.len());
	EXPECT_STREQ("", foo.cstr());

	// create String from char
	String bar('c');
	String baz = 'd';
	EXPECT_EQ(1, bar.len());
	EXPECT_EQ(1, baz.len());
	EXPECT_STREQ("c", bar.cstr());
	EXPECT_STREQ("d", baz.cstr());

	// create String from c-string
	String qux("The cake is a lie");
	String quux = "We don't go to Ravenholm";
	EXPECT_EQ(strlen("The cake is a lie"), qux.len());
	EXPECT_EQ(strlen("We don't go to Ravenholm"), quux.len());
	EXPECT_STREQ("The cake is a lie", qux.cstr());
	EXPECT_STREQ("We don't go to Ravenholm", quux.cstr());
}

TEST(StringTest, Copy)
{
	// create a String
	String foo = "Combustible lemons!";

	// create a new String by copying the previous one
	String bar = foo;

	// make sure things are in order
	EXPECT_STREQ(foo.cstr(), bar.cstr());
	EXPECT_NE(foo.cstr(), bar.cstr()); // pointers should differ
}

TEST(StringTest, Assign)
{
	// create two Strings
	String foo = "I don't want to go...";
	String bar = "Geronimo!";

	// assign foo to be equal to bar
	foo = bar;
	EXPECT_STREQ(foo.cstr(), bar.cstr());

	// also check assignment to c-string
	bar = "Oh, shut up!";
	EXPECT_STRNE(foo.cstr(), bar.cstr());
}

TEST(StringTest, Equality)
{
	// create two Strings
	String foo = "Apple";
	String bar = "Banana";

	// check equlity and inequality operators
	EXPECT_EQ(0, (foo == bar));
	EXPECT_EQ(1, (foo != bar));

	bar = foo;
	EXPECT_EQ(1, (foo == bar));
}

TEST(StringTest, Index)
{
	// create String constant
	String const foo = "abcdefgh";

	// check if indexing works properly
	unsigned int i = 0;
	for (unsigned int c = 'a'; c <= 'h'; ++c, ++i)
	{
		EXPECT_EQ(c, foo[i]);
	}

	// create String variable
	String bar = "faul";

	// check if indexing works properly
	bar[2] = 'i';
	EXPECT_STREQ("fail", bar.cstr());
}

TEST(StringTest, IndexOutOfRange)
{
	// create String
	String foo = "Spaaaaaace";

	// try to index OOR
	EXPECT_THROW(foo[foo.len()] = 'e', std::out_of_range);
}

TEST(StringTest, Concatenate)
{
	// additive concatenation with char
	String foo = "fo";
	foo += 'o';
	EXPECT_STREQ("foo", foo.cstr());

	// additive concatenation with c-string
	foo += "bar";
	EXPECT_STREQ("foobar", foo.cstr());

	// additive concatenation with another String
	foo += String("barfoo");
	EXPECT_STREQ("foobarbarfoo", foo.cstr());

	// concatenation with char
	String const ba = "ba";
	String bar = ba + 'r';
	EXPECT_STREQ("bar", bar.cstr());

	// concatenation with c-string
	String const f = "f";
	foo = f + "oo";
	EXPECT_STREQ("foo", foo.cstr());

	// concatenation with another String
	String foobar = foo + bar;
	EXPECT_STREQ("foobar", foobar.cstr());

}

TEST(StringTest, IO)
{
	// create two Strings
	String foo;
	String const bar = "trololo";

	// extraction
	std::stringstream ss;
	ss << "Allons-y!";
	ss >> foo;
	EXPECT_STREQ("Allons-y!", foo.cstr());

	// insertion
	ss.str("");
	ss.clear();
	ss << bar;
	EXPECT_STREQ("trololo", ss.str().c_str());
}
