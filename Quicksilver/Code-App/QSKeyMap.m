//
//  QSKeyMap.m
//  Quicksilver
//
//  Based on code from http://code.google.com/p/qsb-mac/
//  Copyright 2009 disterics
//
//  Copyright 2008 Google Inc.
//
//  Licensed under the Apache License, Version 2.0 (the "License"); you may not
//  use this file except in compliance with the License.  You may obtain a copy
//  of the License at
// 
//  http://www.apache.org/licenses/LICENSE-2.0
// 
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
//  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
//  License for the specific language governing permissions and limitations under
//  the License.
//

#import "QSKeyMap.h"

@implementation QSKeyMap
+ (id)currentKeyMap {
	KeyMap keyMap;
	GetKeys(keyMap);
	return [[[self alloc] initWithKeyMap:keyMap] autorelease];
}

- (id)init {
	return [super init];
}

- (id)initWithKeyMap:(KeyMap)keyMap {
	if ((self = [super init])) {
		memcpy(keyMap_, keyMap, sizeof(KeyMapByteArray));
	}
	return self;
}

- (id)initWithKeys:(const UInt16 *)keys count:(NSUInteger)count {
	if (!keys || !count) {
		NSLog(@"Did you really mean to call us with Keys being nil "
			  @"or count being 0?");
		return [self init];
	}
	KeyMapByteArray array;
	bzero(array, sizeof(array));
	for (NSUInteger k = 0; k < count; ++k) {
		UInt16 i = keys[k] / 8;
		UInt16 j = keys[k] % 8;
		array[i] |= 1 << j;
	}
	return [self initWithKeyMap:*((KeyMap*)&array)];
}

- (id)copyWithZone:(NSZone *)zone {
	return [[[self class] alloc] initWithKeyMap:*((KeyMap*)&keyMap_)];
}

- (NSUInteger)hash {
	// I tried to design this hash so it hashed better on 64 bit than on 32
	// bit. By keying it to the size of hash we can get a better value for our
	// keymap.
	NSUInteger hash = 0;
	NSUInteger *keyMapHash = (NSUInteger *)keyMap_;
	for (size_t i = 0; i < sizeof(keyMap_) / sizeof(hash); ++i) {
		hash += keyMapHash[i];
	}
	return hash;
}  

- (BOOL)isEqual:(id)keyMap {
	BOOL isEqual = [keyMap isKindOfClass:[self class]];
	if (isEqual) {
		KeyMapByteArray array;
		[keyMap getKeyMap:(KeyMap*)&array];
		isEqual = memcmp(keyMap_, array, sizeof(KeyMapByteArray)) == 0;
	}
	return isEqual;
}

- (NSString*)description {
	NSMutableString *string = [NSMutableString string];
	for (size_t i = 0; i < sizeof(keyMap_); i++) {
		[string appendFormat:@" %02hhX", keyMap_[i]];
	}
	return string;
}

- (QSKeyMap *)keyMapByAddingKey:(UInt16)keyCode {
	KeyMapByteArray array;
	[self getKeyMap:(KeyMap*)&array];
	
	UInt16 i = keyCode / 8;
	UInt16 j = keyCode % 8;
	array[i] |= 1 << j;
	return [[[[self class] alloc] initWithKeyMap:*((KeyMap*)&array)] autorelease];
}

- (QSKeyMap *)keyMapByInverting {
	KeyMapByteArray array;
	for (size_t i = 0; i < sizeof(array); ++i) {
		array[i] = ~keyMap_[i];
	}
	return [[[[self class] alloc] initWithKeyMap:*((KeyMap*)&array)] autorelease];
}

- (void)getKeyMap:(KeyMap*)keyMap {
	if (keyMap) {
		memcpy(*keyMap, keyMap_, sizeof(KeyMapByteArray));
	} else {
		NSLog(@"You probably don't want to call getKeyMap with a NULL ptr");
	}
}

- (BOOL)containsAnyKeyIn:(QSKeyMap *)keyMap {
	BOOL contains = NO;
	KeyMapByteArray array;
	[keyMap getKeyMap:(KeyMap*)&array];
	for (size_t i = 0; i < sizeof(KeyMapByteArray); ++i) {
		if (keyMap_[i] & array[i]) {
			contains = YES;
			break;
		}
	}
	return contains;
}

@end
