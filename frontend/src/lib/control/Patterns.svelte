<script lang="ts">
  import { dndzone } from 'svelte-dnd-action';

  import Block from '$lib/component/Block.svelte'
</script>


<Block>
  <h1>Patterns</h1>

  <ul>
    <li>Fill</li>
    <li>Stripe</li>
    <li>Wave</li>
  </ul>
</Block>

<style>
  ul {
    list-style: none;
    margin: 0;
    padding: 0;
  }

  li {
    padding: .2rem;
    background: var(--button-color);
    margin: .2rem;
  }
  li:hover {
    cursor: pointer;
    background: var(--background-color);
  }
</style>