## Serial Direct Memory Access (DMA)
- DMA allows to easily transfer buffers of data in a non-blocking way.
- DMA uses circular buffer to store the data. *DMA itself is very complex, you can fire half complete interrupt to start processing the data while the other half is still pending. You can use double-buffer mode.*
- When data is sent, enable DMA stream in CR register to fire the sending event again.

**TODO: FIX the bi-directional message send.For now I cant use send_message function to correctly send received data.**