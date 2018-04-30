package main

import (
	"fmt"
	"time"
)

type fsm struct {
	States           map[string]state
	activeState      string
	legalTransitions map[string]map[string]bool
}

func (f *fsm) Init() {
	fmt.Println("Initializing fsm")
	f.States = make(map[string]state)

	initialState := idle{}
	f.addState(initialState)
	f.addState(drive{})
	f.addState(open{})

	for _, s := range f.States {
		s.init()
	}

	f.legalTransitions = make(map[string]map[string]bool)
	for from, _ := range f.States {
		f.legalTransitions[from] = make(map[string]bool)
		for to, _ := range f.States {
			f.legalTransitions[from][to] = true
		}
	}

	f.States[initialState.getName()].begin()
	fmt.Println("fsm initialized", f.States)
}
func (f *fsm) addState(s state) {
	f.States[s.getName()] = s
}
func (f *fsm) Transition(from state, to state) bool {
	if f.legalTransitions[from.getName()][to.getName()] {
		f.States[f.activeState].end()
		f.activeState = to.getName()
		f.States[f.activeState].begin()
		return true
	}
	return false
}
func (f *fsm) PrintLegalTransitions() {
	for from, _ := range f.legalTransitions {
		fmt.Printf("%v -> ", from)
		for to, _ := range f.legalTransitions[from] {
			fmt.Printf("%v ", to)
		}
		fmt.Printf("\n")
	}
}

type state interface {
	init()
	begin()
	end()
	getName() string
}

type stateImpl struct {
}

type idle stateImpl
type drive stateImpl
type open stateImpl

func (s idle) init() {
	fmt.Println("idle init")
}
func (s idle) begin() {
	fmt.Println("idle begin")
}
func (s idle) end() {
	fmt.Println("idle end")
}

func (s idle) getName() string {
	return "idle"
}

func (s drive) init() {
	fmt.Println("drive init")
}
func (s drive) begin() {
	fmt.Println("drive begin")
}
func (s drive) end() {
	fmt.Println("drive end")
}
func (s drive) getName() string {
	return "drive"
}

func (s open) init() {
	fmt.Println("open init")
}
func (s open) begin() {
	fmt.Println("open begin")
}
func (s open) end() {
	fmt.Println("open end")
}
func (s open) getName() string {
	return "open"
}

func main() {
	var f fsm
	f.Init()

	f.PrintLegalTransitions()

	for {
		select {
		case <-time.After(5 * time.Second):
		}
	}

}
