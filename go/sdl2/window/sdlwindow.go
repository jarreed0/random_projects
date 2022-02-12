package main

import (
	"github.com/veandco/go-sdl2/sdl"
)

var (
	bkg                                            sdl.Color
	title                                          string = "SDL2 Window"
	width                                          int32  = 800
	height                                         int32  = 800
	renderer                                       *sdl.Renderer
	window                                         *sdl.Window
	frameCount, timerFPS, lastFrame, fps, lastTime uint32
	setFPS                                         uint32 = 60
	mouse                                          sdl.Point
	mousestate                                     uint32
	keystates                                      = sdl.GetKeyboardState()
	event                                          sdl.Event
	running                                        bool
)

func setColor(r, g, b, a uint8) sdl.Color {
	var c sdl.Color
	c.R = r
	c.G = g
	c.B = b
	c.A = a
	return c
}

func start() {
	sdl.SetHint(sdl.HINT_RENDER_SCALE_QUALITY, "0")
	if err := sdl.Init(sdl.INIT_EVERYTHING); err != nil {
		panic(err)
	}
	window, err := sdl.CreateWindow(title, sdl.WINDOWPOS_UNDEFINED, sdl.WINDOWPOS_UNDEFINED, width, height, sdl.WINDOW_SHOWN)
	if err != nil {
		panic(err)
	}
	renderer, err = sdl.CreateRenderer(window, -1, sdl.RENDERER_ACCELERATED|sdl.RENDERER_PRESENTVSYNC)
	if err != nil {
		panic(err)
	}
	running = true
}

func startSet(t string, w int32, h int32) {
	title = t
	width = w
	height = h
	start()
}

func quit() {
	running = false
	window.Destroy()
	renderer.Destroy()
	sdl.Quit()
}

func loop() {
	lastFrame = sdl.GetTicks()
	if lastFrame >= (lastTime + 1000) {
		lastTime = lastFrame
		fps = frameCount
		frameCount = 0
	}
	input()
}

func input() {
	keystates = sdl.GetKeyboardState()
	for event := sdl.PollEvent(); event != nil; event = sdl.PollEvent() {
		switch event.(type) {
		case *sdl.QuitEvent:
			running = false
			break
		}
	}
	mouse.X, mouse.Y, mousestate = sdl.GetMouseState()
}

func beginRender() {
	renderer.SetDrawColor(bkg.R, bkg.G, bkg.B, bkg.A)
	renderer.Clear()
	frameCount++
	timerFPS = sdl.GetTicks() - lastFrame
	if timerFPS < (1000 / setFPS) {
		sdl.Delay((1000 / setFPS) - timerFPS)
	}
	renderer.SetDrawColor(0, 0, 0, 255)
}

func endRender() {
	renderer.Present()
}

func main() {
	startSet("hello", 300, 300)
	bkg = setColor(255, 0, 255, 255)
	for running {
		loop()
		beginRender()
		//renderer.DrawRect()
		endRender()
		if keystates[sdl.SCANCODE_ESCAPE] != 0 {
			running = false
		}
	}
	quit()
}
