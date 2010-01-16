//
//  QSModifierKeyHandler.h
//  Quicksilver
//
// Singleton class responsible for detecting quicksilver 
// activation via modifier keys.
//
// Copyright 2009 disterics
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#import <Cocoa/Cocoa.h>


@interface QSModifierKeyHandler : NSObject {
	
@private
    EventHotKeyRef hotKey_;  // the hot key we're looking for. 
    NSUInteger hotModifiers_;  // if we are getting double taps, the mods to look for.
    NSUInteger hotModifiersState_;
    NSTimeInterval lastHotModifiersEventCheckedTime_;
    NSUInteger modifierActivationCount;
    NSString *identifier;
    id target;
    SEL action;	
}

// Accessor to get the QSModifierKeyHandler singleton.
//
// Returns:
//  pointer to the QSModifierKeyHandler singleton.
+ (QSModifierKeyHandler *)sharedModifierKeyHandler;

// method that is called when the modifier keys are hit and we are inactive
- (void)modifiersChangedWhileInactive:(NSEvent*)event;

// method that is called when the modifier keys are hit and we are active
- (void)modifiersChangedWhileActive:(NSEvent*)event;

// method that is called when a key changes state and we are active
- (void)keysChangedWhileActive:(NSEvent*)event;

// accessors for the activation modifier 
- (unsigned int) modifierActivationMask;
- (void)setModifierActivationMask:(NSUInteger)newModifierActivationMask;

// accessors for the number of times modifier key 
// should be hit
- (int) modifierActivationCount;
- (void)setModifierActivationCount:(NSUInteger)newModifierActivationCount;

// accessors for the activation delegate
- (id)target;
- (void)setTarget:(id)newTarget;

// accessors for selector to perform on the delegate
- (SEL) action;
- (void)setAction:(SEL)newAction;

// accessors for identifier 
// TODO: is this used?
- (NSString *)identifier;
- (void)setIdentifier:(NSString *)newIdentifier;

// perform seletor on target when activated
- (void)sendAction;

// Returns the amount of time between two clicks to be considered a double click
- (NSTimeInterval)doubleClickTime;

// enable or disable modifier key activation
- (void)enable;
- (void)disable;

@end
