//
//  QSKeyMap.h
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

#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>

// Wrapper around a standard carbon keymap. These are all virtual keycodes
// several of which are defing in Events.h. This is an immutable object.
@interface QSKeyMap : NSObject <NSCopying> {
@private
	KeyMapByteArray keyMap_;
}

// Return an autoreleased keymap representing the current keys that are down
+ (id)currentKeyMap;

// Return an empty keyMap
- (id)init;

// Return a keymap object representing the keyMap
- (id)initWithKeyMap:(KeyMap)keyMap;

// Return a keymap with a |count| size array of |keys| down
- (id)initWithKeys:(const UInt16 *)keys count:(NSUInteger)count;

// Return a new autoreleased key map that has a key added to it
- (QSKeyMap *)keyMapByAddingKey:(UInt16)keyCode;

// Inverts a keymap
- (QSKeyMap *)keyMapByInverting;

// Gets a copy of the key map wrapped by this object
- (void)getKeyMap:(KeyMap *)keyMap;

// Returns true if one or more of the keys in |keyMap| are also in us.
// So if you wanted to check if "M" was down, you would create a keyMap 
// containing "kVK_ANSI_M" and then call 
// [myMap containsAnyKeyIn:[QSKeyMap currentKeyMap]]
- (BOOL)containsAnyKeyIn:(QSKeyMap *)keyMap;
@end
