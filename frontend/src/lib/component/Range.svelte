<script lang='ts'>

  export let min: number = 0
  export let max: number = 0
  export let value = 100

  
  let sliderEl: HTMLInputElement;

  $: sliderWidth = sliderEl?.offsetWidth || 0;
  $: progress = sliderWidth * value/(max-min) + 'px';
</script>

<svelte:window on:resize={() => { sliderWidth = sliderWidth; }} />

<div class='container'>
  <slot name='track'>
    <div class="track"></div>
    <div class="track track-highlight" style:width={progress}></div>
  </slot>
  
  <input bind:this={sliderEl} type="range" {min} {max} bind:value {...$$props}>
</div>



<style>
  .container {
    position: relative;
    z-index: 0;
    
    height: 2rem;
    margin: var(--margin);
  } 
  input[type="range"] {
    background: none;
    -webkit-appearance: none;
    height: 1rem;
    width: 100%;
    margin: 0;

    position: absolute;
    left: 0;
    bottom: var(--margin);
    top: var(--margin);
    right: 0;
  }
  input::-webkit-slider-thumb {
    -webkit-appearance: none;
    appearance: none;
    width: 1rem;
    height: 2rem;
    box-shadow: var(--thumb-shadow, -1px 1px 5px rgba(0,0,0,.4)); 
    background: var(--thumb-color, #04AA6D); /*color*/
    border-radius: 0;
    border: none;
  }
  input::-moz-range-thumb {
    width: 1rem;
    height: 2rem;
    box-shadow: var(--thumb-shadow, -1px 1px 5px rgba(0,0,0,.4)); 
    background: var(--thumb-color, #04AA6D); /*color*/
    border-radius: 0;
    border: none;
  }
  .track, :global([slot=track]) {
    width: 100%;
    height: 4px;
    background: var(--color); /*color*/
    pointer-events: none;

    position: absolute;
    top: calc(1rem - 2px);;
  }
  .track-highlight {
    background: var(--thumb-color); /*color*/
  }
</style>