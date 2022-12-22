<script lang="ts">
  import ColorPicker from 'svelte-awesome-color-picker';
  import type { RgbaColor} from 'svelte-awesome-color-picker'
  import { browser } from '$app/environment';


  let rgb : RgbaColor
  let count: number = 20

  const debounced = (func: (...args: any[]) => any, timeout: number) => {
    let isCalled = false
    let lastArgs: any[] | null
    let timer: NodeJS.Timeout

    let timeoutcb = () => {
      if (lastArgs) {
        func.call(lastArgs)
        lastArgs = null
        isCalled = false
        timer = setTimeout(timeoutcb, timeout)
      }
    }

    return (...args: any[]) => {
      if (isCalled) {
        lastArgs = args
      } else {
        func.call(args)
        isCalled = true

        timer = setTimeout(timeoutcb, timeout)
      }
    }
  }

  const send = (color: RgbaColor, count: number) => {
    const data = {
      color: color ?  {'r':color.r, 'g':color.g, 'b': color.b} : {r:255,g:0,b:0},
      count
    }
      fetch("color", {
        method: 'POST',
        body: JSON.stringify(data),
        headers: { 'content-type': 'application/json'
      }}) 
  }

  $: browser && send(rgb, count)

</script>

<h1>Lights</h1>

<ColorPicker bind:rgb isInput={false}  />

<input type='range' min={1} max={80} bind:value={count} />