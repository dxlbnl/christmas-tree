<script lang='ts'>
  export let as = 'section'
</script>

<svelte:element class='element' this={as} {...$$props}>
  <slot />
</svelte:element>

<style>
  .element {
    background-color: var(--background);
    border: var(--border);

    padding: var(--margin);
  }
</style>