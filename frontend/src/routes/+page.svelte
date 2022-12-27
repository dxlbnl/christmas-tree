<script lang="ts">
  import { onMount } from 'svelte';
  import ColorPicker from 'svelte-awesome-color-picker';
  import type { RgbaColor, HsvaColor } from 'svelte-awesome-color-picker'

  
  type HSVColor = {
      h: number;
      s: number;
      v: number;
  }
  interface Data {
    trickle?: {
      color?: RgbaColor,
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
  let loaded = false;

  let color1: HsvaColor = {h: 0, s: 100, v: 100, a: 0}
  let color2: HsvaColor = {h: 0, s: 100, v: 100, a: 0}
  let color3: HsvaColor = {h: 0, s: 100, v: 100, a: 0}
  let speed1 = 1230
  let speed2 = 136
  let speed3 = 500
  let trickle = { color: {r:0, g: 0, b: 0, a:0}}
  let twinkle = { count: 10 }

  const convertToHSV = (c: HsvaColor): HSVColor => ({
    h: c.h/360 * 255 |0,
    s: c.s/100 * 255 |0,
    v: c.v/100 * 255 |0,
  })
  const convertFromHSV = (c: HSVColor): HsvaColor => ({
    h: c.h/255 * 360 |0,
    s: c.s/255 * 100 |0,
    v: c.v/255 * 100 |0,
    a: 1
  })

  onMount(async () => {
    const req = await fetch('/config.json')

    const data: Data = await req.json()

    if (data.tree) {
      color1 = convertFromHSV(data.tree.color1)
      color2 = convertFromHSV(data.tree.color2)
      color3 = convertFromHSV(data.tree.color3)
      speed1 = data.tree.speed1
      speed2 = data.tree.speed2
      speed3 = data.tree.speed3
    }

    if (data.trickle?.color) {
      trickle.color = data.trickle.color
    }

    if (data.twinkle?.count) {
      twinkle.count = data.twinkle.count
    }

    loaded = true;
  })


  const send = async (data: Data) => {
    if (timer) {
      cachedData = {...cachedData, ...data}
    } else {
      fetch("/color", {
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

  $: loaded && send({
    tree: {
      color1: convertToHSV(color1),
      color2: convertToHSV(color2),
      color3: convertToHSV(color3),
      speed1,
      speed2,
      speed3,
    }
  })
  $: loaded && send({ twinkle })
  $: loaded && send({ trickle })
</script>

<h1>Lights</h1>

{#if !loaded}
  <p>Loading...</p>
{:else}
  <ColorPicker isInput={false} bind:rgb={trickle.color} />

  <input type='range' min={0} max={150} bind:value={twinkle.count} />

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
{/if}

<style>
  .row {
    display: flex;
  }
</style>