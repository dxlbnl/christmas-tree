<script lang="ts">
  import Range from './Range.svelte'
  import { colord } from 'colord'

  export let hue = 0;
  export let saturation = 0;
  export let value = 0;

  const steps = 30
</script>

<section>
  <label for=color>Color</label>  

  <div class='hue' style:--thumb-color={colord({ h: hue, s: 100, v: 100}).toHslString()} >
    <Range
      id='color'
      min={0}
      max={360}
      bind:value={hue}
    >
      <svg
        slot='track'
        viewBox="0 0 {steps} 1"
        preserveAspectRatio=none
        shape-rendering="crispEdges"
      >
        {#each Array(steps).fill(0) as _, index}
          <rect
            fill={colord({ h: 360/steps * index, s: 100, v: 100}).toHslString()}
            x={index}
            width={1}
            height={1}
          />
        {/each}
      </svg>
    </Range>
  </div>

  <div class='saturation' style:--thumb-color={colord({ h: hue, s: saturation, v: 100}).toHslString()} >
    <Range
      min={0}
      max={100}
      bind:value={saturation}
    >
      <svg
        slot='track'
        viewBox="0 0 {steps} 1"
        preserveAspectRatio=none
        shape-rendering="crispEdges"
      >
        {#each Array(steps).fill(0) as _, index}
          <rect
            fill={colord({ h: hue, s: 100/steps * index, v: 100}).toHslString()}
            x={index}
            width={1}
            height={1}
          />
        {/each}
      </svg>
    </Range>
  </div>

  <div class='value' style:--thumb-color={colord({ h: hue, s: saturation, v: value}).toHslString()} >
    <Range
      min={0}
      max={100}
      bind:value={value}
    >
      <svg
        slot='track'
        viewBox="0 0 {steps} 1"
        preserveAspectRatio=none
        shape-rendering="crispEdges"
      >
        {#each Array(steps).fill(0) as _, index}
          <rect
            fill={colord({ h: hue, s: saturation, v: 100/steps * index}).toHslString()}
            x={index}
            width={1}
            height={1}
          />
        {/each}
      </svg>
    </Range>
  </div>

  <div class='output' style:background={colord({ h: hue, s: saturation, v: value}).toHslString()} />
</section>

<style>
  svg {
    height:1.5rem;
    top: calc(var(--margin)/2);

    background: none;
  }

  section {
    display: grid;
    grid-template:
      "label label" auto 
      "hue output" auto
      "saturation output" auto
      "value output" auto / auto 5rem;
  }

  label {
    grid-area: label;
  }
  .hue {
    grid-area: hue;
  }
  .saturation {
    grid-area: saturation;
  }
  .value {
    grid-area: value;
  }
  .output {
    grid-area: output;
  }
</style>