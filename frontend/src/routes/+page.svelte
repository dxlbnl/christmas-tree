<script lang="ts">
  import Select from '$lib/Select.svelte'
  import { config } from '$lib/config'
  import type { PageData } from './$types';

  export let data: PageData;
</script>

<!-- svelte-ignore a11y-label-has-associated-control -->
<label>
  Program:
  <Select
    options={data.programs}
    on:change={({ target }) => config({ program: target.value })}
  />
</label>

<label>
  Brightness:
  <input type='range' min=1 max=255 on:change={({ target }) => config({ brightness: target.value })} />
</label>


<style>
  label {
    display: block;
  }
</style>
