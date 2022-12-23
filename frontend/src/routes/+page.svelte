<script lang="ts">
  import ColorPicker from 'svelte-awesome-color-picker';
  import type { RgbaColor, HsvaColor } from 'svelte-awesome-color-picker'
  type RGBColor = {
      r: number;
      g: number;
      b: number;
  }
  type HSVColor = {
      h: number;
      s: number;
      v: number;
  }
  interface Data {
    trickle?: {
      color?: RGBColor,
    },
    twinkle?: {
      count?: number;
    },
    tree?: {
      color1: HSVColor;
      color2: HSVColor;
      color3: HSVColor;
      speed1: number;
      speed2: number;
      speed3: number;
    }
  }

  let timer: NodeJS.Timeout | null;
  let cachedData: Data | null
  const send = async (data: Data) => {
    if (timer) {
      cachedData = {...cachedData, ...data}
    } else {
      fetch("http://esp-lights.local/color", {
        method: 'POST',
        body: JSON.stringify({...cachedData, ...data}),
        headers: { 'content-type': 'application/json'
      }})
      cachedData = null;
      timer = setTimeout(() => {
        timer = null;
        if (cachedData) {
          send(cachedData)
        }
      }, 100)
    }
  }

  // $: browser && send(rgb, count)

  let color1: HsvaColor = {h: 0, s: 100, v: 100, a: 0}
  let color2: HsvaColor = {h: 0, s: 100, v: 100, a: 0}
  let color3: HsvaColor = {h: 0, s: 100, v: 100, a: 0}
  let speed1 = 1230
  let speed2 = 136
  let speed3 = 500
  const convertHSV = (c: HsvaColor): HSVColor => ({
    h: c.h/360 * 255 |0,
    s: c.s/100 * 255 |0,
    v: c.v/100 * 255 |0,
  })
  $: send({
    tree: {
      color1: convertHSV(color1),
      color2: convertHSV(color2),
      color3: convertHSV(color3),
      speed1,
      speed2,
      speed3,
    }
  })
</script>

<h1>Lights</h1>

<ColorPicker isInput={false} on:input={(e) => send({ trickle: {color: e.detail.rgb } })}  />

<input type='range' min={0} max={150} on:input={(e) => send({ twinkle: { count: e.target.valueAsNumber }})} />

<section>
  <section class='row'>
    <ColorPicker isInput={false} bind:hsv={color1}/>
    <ColorPicker isInput={false} bind:hsv={color2}/>
    <ColorPicker isInput={false} bind:hsv={color3}/>
  </section>
    <input type='range' min={100} max={3000} bind:value={speed1}/>
    <input type='range' min={100} max={3000} bind:value={speed2}/>
    <input type='range' min={100} max={3000} bind:value={speed3}/>

</section>

<style>
  .row {
    display: flex;
  }
</style>